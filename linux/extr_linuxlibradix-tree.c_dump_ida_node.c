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
struct radix_tree_node {unsigned long shift; void** slots; int /*<<< orphan*/  count; int /*<<< orphan*/ ** tags; int /*<<< orphan*/  parent; int /*<<< orphan*/  offset; } ;
struct ida_bitmap {int /*<<< orphan*/ * bitmap; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_LONG ; 
 unsigned long IDA_BITMAP_BITS ; 
 unsigned long IDA_BITMAP_LONGS ; 
 unsigned long RADIX_TREE_EXCEPTIONAL_SHIFT ; 
 unsigned long RADIX_TREE_MAP_MASK ; 
 unsigned long RADIX_TREE_MAP_SIZE ; 
 struct radix_tree_node* entry_to_node (void*) ; 
 unsigned long node_maxindex (struct radix_tree_node*) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ radix_tree_exceptional_entry (void*) ; 
 scalar_t__ radix_tree_is_internal_node (void*) ; 

__attribute__((used)) static void dump_ida_node(void *entry, unsigned long index)
{
	unsigned long i;

	if (!entry)
		return;

	if (radix_tree_is_internal_node(entry)) {
		struct radix_tree_node *node = entry_to_node(entry);

		pr_debug("ida node: %p offset %d indices %lu-%lu parent %p free %lx shift %d count %d\n",
			node, node->offset, index * IDA_BITMAP_BITS,
			((index | node_maxindex(node)) + 1) *
				IDA_BITMAP_BITS - 1,
			node->parent, node->tags[0][0], node->shift,
			node->count);
		for (i = 0; i < RADIX_TREE_MAP_SIZE; i++)
			dump_ida_node(node->slots[i],
					index | (i << node->shift));
	} else if (radix_tree_exceptional_entry(entry)) {
		pr_debug("ida excp: %p offset %d indices %lu-%lu data %lx\n",
				entry, (int)(index & RADIX_TREE_MAP_MASK),
				index * IDA_BITMAP_BITS,
				index * IDA_BITMAP_BITS + BITS_PER_LONG -
					RADIX_TREE_EXCEPTIONAL_SHIFT,
				(unsigned long)entry >>
					RADIX_TREE_EXCEPTIONAL_SHIFT);
	} else {
		struct ida_bitmap *bitmap = entry;

		pr_debug("ida btmp: %p offset %d indices %lu-%lu data", bitmap,
				(int)(index & RADIX_TREE_MAP_MASK),
				index * IDA_BITMAP_BITS,
				(index + 1) * IDA_BITMAP_BITS - 1);
		for (i = 0; i < IDA_BITMAP_LONGS; i++)
			pr_cont(" %lx", bitmap->bitmap[i]);
		pr_cont("\n");
	}
}