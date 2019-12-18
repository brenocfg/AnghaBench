#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ color; TYPE_1__* parent; struct TYPE_15__* right; struct TYPE_15__* left; } ;
struct TYPE_14__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* freefunc ) (TYPE_3__*,int /*<<< orphan*/ ) ;TYPE_3__* root; } ;
struct TYPE_13__ {TYPE_3__* right; TYPE_3__* left; } ;
typedef  TYPE_2__ RBTree ;
typedef  TYPE_3__ RBTNode ;

/* Variables and functions */
 scalar_t__ RBTBLACK ; 
 TYPE_3__* RBTNIL ; 
 int /*<<< orphan*/  rbt_copy_data (TYPE_2__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  rbt_delete_fixup (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rbt_delete_node(RBTree *rbt, RBTNode *z)
{
	RBTNode    *x,
			   *y;

	/* This is just paranoia: we should only get called on a valid node */
	if (!z || z == RBTNIL)
		return;

	/*
	 * y is the node that will actually be removed from the tree.  This will
	 * be z if z has fewer than two children, or the tree successor of z
	 * otherwise.
	 */
	if (z->left == RBTNIL || z->right == RBTNIL)
	{
		/* y has a RBTNIL node as a child */
		y = z;
	}
	else
	{
		/* find tree successor */
		y = z->right;
		while (y->left != RBTNIL)
			y = y->left;
	}

	/* x is y's only child */
	if (y->left != RBTNIL)
		x = y->left;
	else
		x = y->right;

	/* Remove y from the tree. */
	x->parent = y->parent;
	if (y->parent)
	{
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	else
	{
		rbt->root = x;
	}

	/*
	 * If we removed the tree successor of z rather than z itself, then move
	 * the data for the removed node to the one we were supposed to remove.
	 */
	if (y != z)
		rbt_copy_data(rbt, z, y);

	/*
	 * Removing a black node might make some paths from root to leaf contain
	 * fewer black nodes than others, or it might make two red nodes adjacent.
	 */
	if (y->color == RBTBLACK)
		rbt_delete_fixup(rbt, x);

	/* Now we can recycle the y node */
	if (rbt->freefunc)
		rbt->freefunc(y, rbt->arg);
}