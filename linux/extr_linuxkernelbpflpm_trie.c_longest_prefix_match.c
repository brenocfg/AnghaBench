#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpm_trie_node {int* data; size_t prefixlen; } ;
struct lpm_trie {size_t data_size; } ;
struct bpf_lpm_trie_key {int* data; size_t prefixlen; } ;

/* Variables and functions */
 int fls (int) ; 
 size_t min (size_t,size_t) ; 

__attribute__((used)) static size_t longest_prefix_match(const struct lpm_trie *trie,
				   const struct lpm_trie_node *node,
				   const struct bpf_lpm_trie_key *key)
{
	size_t prefixlen = 0;
	size_t i;

	for (i = 0; i < trie->data_size; i++) {
		size_t b;

		b = 8 - fls(node->data[i] ^ key->data[i]);
		prefixlen += b;

		if (prefixlen >= node->prefixlen || prefixlen >= key->prefixlen)
			return min(node->prefixlen, key->prefixlen);

		if (b < 8)
			break;
	}

	return prefixlen;
}