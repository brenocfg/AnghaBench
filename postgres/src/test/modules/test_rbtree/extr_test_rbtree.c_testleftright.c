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
struct TYPE_2__ {int key; } ;
typedef  int /*<<< orphan*/  RBTreeIterator ;
typedef  int /*<<< orphan*/  RBTree ;
typedef  TYPE_1__ IntRBTreeNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LeftRightWalk ; 
 int /*<<< orphan*/ * create_int_rbtree () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rbt_begin_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rbt_iterate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbt_populate (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
testleftright(int size)
{
	RBTree	   *tree = create_int_rbtree();
	IntRBTreeNode *node;
	RBTreeIterator iter;
	int			lastKey = -1;
	int			count = 0;

	/* check iteration over empty tree */
	rbt_begin_iterate(tree, LeftRightWalk, &iter);
	if (rbt_iterate(&iter) != NULL)
		elog(ERROR, "left-right walk over empty tree produced an element");

	/* fill tree with consecutive natural numbers */
	rbt_populate(tree, size, 1);

	/* iterate over the tree */
	rbt_begin_iterate(tree, LeftRightWalk, &iter);

	while ((node = (IntRBTreeNode *) rbt_iterate(&iter)) != NULL)
	{
		/* check that order is increasing */
		if (node->key <= lastKey)
			elog(ERROR, "left-right walk gives elements not in sorted order");
		lastKey = node->key;
		count++;
	}

	if (lastKey != size - 1)
		elog(ERROR, "left-right walk did not reach end");
	if (count != size)
		elog(ERROR, "left-right walk missed some elements");
}