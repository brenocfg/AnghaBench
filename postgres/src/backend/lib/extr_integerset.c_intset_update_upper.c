#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64 ;
struct TYPE_11__ {scalar_t__ level; } ;
typedef  TYPE_2__ intset_node ;
struct TYPE_12__ {TYPE_1__* items; } ;
typedef  TYPE_3__ intset_leaf_node ;
struct TYPE_13__ {int level; int num_items; TYPE_2__** downlinks; void** values; } ;
typedef  TYPE_4__ intset_internal_node ;
struct TYPE_14__ {int num_levels; TYPE_2__** rightmost_nodes; TYPE_2__* root; } ;
struct TYPE_10__ {void* first; } ;
typedef  TYPE_5__ IntegerSet ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int MAX_INTERNAL_ITEMS ; 
 int MAX_TREE_LEVELS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* intset_new_internal_node (TYPE_5__*) ; 

__attribute__((used)) static void
intset_update_upper(IntegerSet *intset, int level, intset_node *child,
					uint64 child_key)
{
	intset_internal_node *parent;

	Assert(level > 0);

	/*
	 * Create a new root node, if necessary.
	 */
	if (level >= intset->num_levels)
	{
		intset_node *oldroot = intset->root;
		uint64		downlink_key;

		/* MAX_TREE_LEVELS should be more than enough, this shouldn't happen */
		if (intset->num_levels == MAX_TREE_LEVELS)
			elog(ERROR, "could not expand integer set, maximum number of levels reached");
		intset->num_levels++;

		/*
		 * Get the first value on the old root page, to be used as the
		 * downlink.
		 */
		if (intset->root->level == 0)
			downlink_key = ((intset_leaf_node *) oldroot)->items[0].first;
		else
			downlink_key = ((intset_internal_node *) oldroot)->values[0];

		parent = intset_new_internal_node(intset);
		parent->level = level;
		parent->values[0] = downlink_key;
		parent->downlinks[0] = oldroot;
		parent->num_items = 1;

		intset->root = (intset_node *) parent;
		intset->rightmost_nodes[level] = (intset_node *) parent;
	}

	/*
	 * Place the downlink on the parent page.
	 */
	parent = (intset_internal_node *) intset->rightmost_nodes[level];

	if (parent->num_items < MAX_INTERNAL_ITEMS)
	{
		parent->values[parent->num_items] = child_key;
		parent->downlinks[parent->num_items] = child;
		parent->num_items++;
	}
	else
	{
		/*
		 * Doesn't fit.  Allocate new parent, with the downlink as the first
		 * item on it, and recursively insert the downlink to the new parent
		 * to the grandparent.
		 */
		parent = intset_new_internal_node(intset);
		parent->level = level;
		parent->values[0] = child_key;
		parent->downlinks[0] = child;
		parent->num_items = 1;

		intset->rightmost_nodes[level] = (intset_node *) parent;

		intset_update_upper(intset, level + 1, (intset_node *) parent, child_key);
	}
}