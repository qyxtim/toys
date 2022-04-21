#pragma once

#include <cstddef>
#include <map>
#include <memory>
#include <vector>

class Trie
{
private:
    struct Node
    {
        std::unique_ptr<Node> left, right;
        uint8_t c;

        bool isLeaf() const
        {
            return !(left) && !(right);
        }
    };

    std::unique_ptr<Node> root;
    size_t frequency;

public:
    Trie(uint8_t c, size_t frequency);
    Trie(std::unique_ptr<Node> &&root);
    Trie(const Trie &other) = delete;
    Trie &operator=(const Trie &other) = delete;
    Trie(Trie &&other);
    Trie &operator=(Trie &&other);

    void merge(Trie &&other);

    friend bool operator<(const Trie &lhs, const Trie &rhs);
    friend class LookupTable;
    friend class Huffman;
};

bool operator<(const Trie &lhs, const Trie &rhs);

class LookupTable
{
private:
    std::map<uint8_t, std::vector<bool>> table;

private:
    void buildTable(const std::unique_ptr<Trie::Node> &ptr, std::vector<bool> &bits);

public:
    LookupTable(const Trie &t);

    const std::vector<bool> &lookup(uint8_t c) const;
};