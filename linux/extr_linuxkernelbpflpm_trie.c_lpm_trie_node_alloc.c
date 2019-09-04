#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lpm_trie_node {size_t data; scalar_t__ flags; } ;
struct TYPE_2__ {size_t value_size; int /*<<< orphan*/  numa_node; } ;
struct lpm_trie {size_t data_size; TYPE_1__ map; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int __GFP_NOWARN ; 
 struct lpm_trie_node* kmalloc_node (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 

__attribute__((used)) static struct lpm_trie_node *lpm_trie_node_alloc(const struct lpm_trie *trie,
						 const void *value)
{
	struct lpm_trie_node *node;
	size_t size = sizeof(struct lpm_trie_node) + trie->data_size;

	if (value)
		size += trie->map.value_size;

	node = kmalloc_node(size, GFP_ATOMIC | __GFP_NOWARN,
			    trie->map.numa_node);
	if (!node)
		return NULL;

	node->flags = 0;

	if (value)
		memcpy(node->data + trie->data_size, value,
		       trie->map.value_size);

	return node;
}