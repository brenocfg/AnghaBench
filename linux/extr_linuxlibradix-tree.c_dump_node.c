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
struct radix_tree_node {unsigned long shift; void** slots; int /*<<< orphan*/  exceptional; int /*<<< orphan*/  count; int /*<<< orphan*/ ** tags; int /*<<< orphan*/  parent; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 unsigned long RADIX_TREE_MAP_SIZE ; 
 void* RADIX_TREE_RETRY ; 
 struct radix_tree_node* entry_to_node (void*) ; 
 scalar_t__ is_sibling_entry (struct radix_tree_node*,void*) ; 
 unsigned long node_maxindex (struct radix_tree_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,unsigned long,unsigned long,...) ; 
 int /*<<< orphan*/  radix_tree_is_internal_node (void*) ; 

__attribute__((used)) static void dump_node(struct radix_tree_node *node, unsigned long index)
{
	unsigned long i;

	pr_debug("radix node: %p offset %d indices %lu-%lu parent %p tags %lx %lx %lx shift %d count %d exceptional %d\n",
		node, node->offset, index, index | node_maxindex(node),
		node->parent,
		node->tags[0][0], node->tags[1][0], node->tags[2][0],
		node->shift, node->count, node->exceptional);

	for (i = 0; i < RADIX_TREE_MAP_SIZE; i++) {
		unsigned long first = index | (i << node->shift);
		unsigned long last = first | ((1UL << node->shift) - 1);
		void *entry = node->slots[i];
		if (!entry)
			continue;
		if (entry == RADIX_TREE_RETRY) {
			pr_debug("radix retry offset %ld indices %lu-%lu parent %p\n",
					i, first, last, node);
		} else if (!radix_tree_is_internal_node(entry)) {
			pr_debug("radix entry %p offset %ld indices %lu-%lu parent %p\n",
					entry, i, first, last, node);
		} else if (is_sibling_entry(node, entry)) {
			pr_debug("radix sblng %p offset %ld indices %lu-%lu parent %p val %p\n",
					entry, i, first, last, node,
					*(void **)entry_to_node(entry));
		} else {
			dump_node(entry_to_node(entry), first);
		}
	}
}