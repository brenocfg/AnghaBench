#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_8__ {scalar_t__ first; int /*<<< orphan*/  codeword; } ;
typedef  TYPE_1__ leaf_item ;
struct TYPE_9__ {int level; } ;
typedef  TYPE_2__ intset_node ;
struct TYPE_10__ {TYPE_1__* items; int /*<<< orphan*/  num_items; } ;
typedef  TYPE_3__ intset_leaf_node ;
struct TYPE_11__ {scalar_t__* values; scalar_t__ num_items; TYPE_2__** downlinks; } ;
typedef  TYPE_4__ intset_internal_node ;
struct TYPE_12__ {scalar_t__ num_buffered_values; scalar_t__* buffered_values; int num_levels; TYPE_2__* root; } ;
typedef  TYPE_5__ IntegerSet ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int intset_binsrch_leaf (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int intset_binsrch_uint64 (scalar_t__,scalar_t__*,scalar_t__,int) ; 
 scalar_t__ simple8b_contains (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

bool
intset_is_member(IntegerSet *intset, uint64 x)
{
	intset_node *node;
	intset_leaf_node *leaf;
	int			level;
	int			itemno;
	leaf_item  *item;

	/*
	 * The value might be in the buffer of newly-added values.
	 */
	if (intset->num_buffered_values > 0 && x >= intset->buffered_values[0])
	{
		int			itemno;

		itemno = intset_binsrch_uint64(x,
									   intset->buffered_values,
									   intset->num_buffered_values,
									   false);
		if (itemno >= intset->num_buffered_values)
			return false;
		else
			return (intset->buffered_values[itemno] == x);
	}

	/*
	 * Start from the root, and walk down the B-tree to find the right leaf
	 * node.
	 */
	if (!intset->root)
		return false;
	node = intset->root;
	for (level = intset->num_levels - 1; level > 0; level--)
	{
		intset_internal_node *n = (intset_internal_node *) node;

		Assert(node->level == level);

		itemno = intset_binsrch_uint64(x, n->values, n->num_items, true);
		if (itemno == 0)
			return false;
		node = n->downlinks[itemno - 1];
	}
	Assert(node->level == 0);
	leaf = (intset_leaf_node *) node;

	/*
	 * Binary search to find the right item on the leaf page
	 */
	itemno = intset_binsrch_leaf(x, leaf->items, leaf->num_items, true);
	if (itemno == 0)
		return false;
	item = &leaf->items[itemno - 1];

	/* Is this a match to the first value on the item? */
	if (item->first == x)
		return true;
	Assert(x > item->first);

	/* Is it in the packed codeword? */
	if (simple8b_contains(item->codeword, x, item->first))
		return true;

	return false;
}