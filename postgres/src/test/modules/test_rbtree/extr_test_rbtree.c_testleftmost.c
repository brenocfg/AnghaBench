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
struct TYPE_2__ {scalar_t__ key; } ;
typedef  int /*<<< orphan*/  RBTree ;
typedef  TYPE_1__ IntRBTreeNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * create_int_rbtree () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * rbt_leftmost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbt_populate (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
testleftmost(int size)
{
	RBTree	   *tree = create_int_rbtree();
	IntRBTreeNode *result;

	/* Check that empty tree has no leftmost element */
	if (rbt_leftmost(tree) != NULL)
		elog(ERROR, "leftmost node of empty tree is not NULL");

	/* fill tree with consecutive natural numbers */
	rbt_populate(tree, size, 1);

	/* Check that leftmost element is the smallest one */
	result = (IntRBTreeNode *) rbt_leftmost(tree);
	if (result == NULL || result->key != 0)
		elog(ERROR, "rbt_leftmost gave wrong result");
}