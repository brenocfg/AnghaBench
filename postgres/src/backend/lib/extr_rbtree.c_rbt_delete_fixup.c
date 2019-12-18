#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ color; struct TYPE_10__* parent; struct TYPE_10__* left; struct TYPE_10__* right; } ;
struct TYPE_9__ {TYPE_2__* root; } ;
typedef  TYPE_1__ RBTree ;
typedef  TYPE_2__ RBTNode ;

/* Variables and functions */
 scalar_t__ RBTBLACK ; 
 scalar_t__ RBTRED ; 
 int /*<<< orphan*/  rbt_rotate_left (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  rbt_rotate_right (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void
rbt_delete_fixup(RBTree *rbt, RBTNode *x)
{
	/*
	 * x is always a black node.  Initially, it is the former child of the
	 * deleted node.  Each iteration of this loop moves it higher up in the
	 * tree.
	 */
	while (x != rbt->root && x->color == RBTBLACK)
	{
		/*
		 * Left and right cases are symmetric.  Any nodes that are children of
		 * x have a black-height one less than the remainder of the nodes in
		 * the tree.  We rotate and recolor nodes to move the problem up the
		 * tree: at some stage we'll either fix the problem, or reach the root
		 * (where the black-height is allowed to decrease).
		 */
		if (x == x->parent->left)
		{
			RBTNode    *w = x->parent->right;

			if (w->color == RBTRED)
			{
				w->color = RBTBLACK;
				x->parent->color = RBTRED;

				rbt_rotate_left(rbt, x->parent);
				w = x->parent->right;
			}

			if (w->left->color == RBTBLACK && w->right->color == RBTBLACK)
			{
				w->color = RBTRED;

				x = x->parent;
			}
			else
			{
				if (w->right->color == RBTBLACK)
				{
					w->left->color = RBTBLACK;
					w->color = RBTRED;

					rbt_rotate_right(rbt, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = RBTBLACK;
				w->right->color = RBTBLACK;

				rbt_rotate_left(rbt, x->parent);
				x = rbt->root;	/* Arrange for loop to terminate. */
			}
		}
		else
		{
			RBTNode    *w = x->parent->left;

			if (w->color == RBTRED)
			{
				w->color = RBTBLACK;
				x->parent->color = RBTRED;

				rbt_rotate_right(rbt, x->parent);
				w = x->parent->left;
			}

			if (w->right->color == RBTBLACK && w->left->color == RBTBLACK)
			{
				w->color = RBTRED;

				x = x->parent;
			}
			else
			{
				if (w->left->color == RBTBLACK)
				{
					w->right->color = RBTBLACK;
					w->color = RBTRED;

					rbt_rotate_left(rbt, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = RBTBLACK;
				w->left->color = RBTBLACK;

				rbt_rotate_right(rbt, x->parent);
				x = rbt->root;	/* Arrange for loop to terminate. */
			}
		}
	}
	x->color = RBTBLACK;
}