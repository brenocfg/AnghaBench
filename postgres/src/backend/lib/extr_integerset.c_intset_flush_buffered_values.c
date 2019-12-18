#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
struct TYPE_8__ {int first; int /*<<< orphan*/  codeword; } ;
typedef  TYPE_1__ leaf_item ;
typedef  int /*<<< orphan*/  intset_node ;
struct TYPE_9__ {scalar_t__ num_items; TYPE_1__* items; struct TYPE_9__* next; } ;
typedef  TYPE_2__ intset_leaf_node ;
struct TYPE_10__ {int* buffered_values; int num_buffered_values; int num_levels; int /*<<< orphan*/ ** rightmost_nodes; TYPE_2__* leftmost_leaf; int /*<<< orphan*/ * root; } ;
typedef  TYPE_3__ IntegerSet ;

/* Variables and functions */
 scalar_t__ MAX_LEAF_ITEMS ; 
 int MAX_VALUES_PER_LEAF_ITEM ; 
 TYPE_2__* intset_new_leaf_node (TYPE_3__*) ; 
 int /*<<< orphan*/  intset_update_upper (TYPE_3__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  simple8b_encode (int*,int*,int) ; 

__attribute__((used)) static void
intset_flush_buffered_values(IntegerSet *intset)
{
	uint64	   *values = intset->buffered_values;
	uint64		num_values = intset->num_buffered_values;
	int			num_packed = 0;
	intset_leaf_node *leaf;

	leaf = (intset_leaf_node *) intset->rightmost_nodes[0];

	/*
	 * If the tree is completely empty, create the first leaf page, which is
	 * also the root.
	 */
	if (leaf == NULL)
	{
		/*
		 * This is the very first item in the set.
		 *
		 * Allocate root node. It's also a leaf.
		 */
		leaf = intset_new_leaf_node(intset);

		intset->root = (intset_node *) leaf;
		intset->leftmost_leaf = leaf;
		intset->rightmost_nodes[0] = (intset_node *) leaf;
		intset->num_levels = 1;
	}

	/*
	 * If there are less than MAX_VALUES_PER_LEAF_ITEM values in the buffer,
	 * stop.  In most cases, we cannot encode that many values in a single
	 * value, but this way, the encoder doesn't have to worry about running
	 * out of input.
	 */
	while (num_values - num_packed >= MAX_VALUES_PER_LEAF_ITEM)
	{
		leaf_item	item;
		int			num_encoded;

		/*
		 * Construct the next leaf item, packing as many buffered values as
		 * possible.
		 */
		item.first = values[num_packed];
		item.codeword = simple8b_encode(&values[num_packed + 1],
										&num_encoded,
										item.first);

		/*
		 * Add the item to the node, allocating a new node if the old one is
		 * full.
		 */
		if (leaf->num_items >= MAX_LEAF_ITEMS)
		{
			/* Allocate new leaf and link it to the tree */
			intset_leaf_node *old_leaf = leaf;

			leaf = intset_new_leaf_node(intset);
			old_leaf->next = leaf;
			intset->rightmost_nodes[0] = (intset_node *) leaf;
			intset_update_upper(intset, 1, (intset_node *) leaf, item.first);
		}
		leaf->items[leaf->num_items++] = item;

		num_packed += 1 + num_encoded;
	}

	/*
	 * Move any remaining buffered values to the beginning of the array.
	 */
	if (num_packed < intset->num_buffered_values)
	{
		memmove(&intset->buffered_values[0],
				&intset->buffered_values[num_packed],
				(intset->num_buffered_values - num_packed) * sizeof(uint64));
	}
	intset->num_buffered_values -= num_packed;
}