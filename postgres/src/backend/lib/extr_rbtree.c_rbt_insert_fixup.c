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
 void* RBTBLACK ; 
 scalar_t__ RBTRED ; 
 int /*<<< orphan*/  rbt_rotate_left (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  rbt_rotate_right (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void
rbt_insert_fixup(RBTree *rbt, RBTNode *x)
{
	/*
	 * x is always a red node.  Initially, it is the newly inserted node. Each
	 * iteration of this loop moves it higher up in the tree.
	 */
	while (x != rbt->root && x->parent->color == RBTRED)
	{
		/*
		 * x and x->parent are both red.  Fix depends on whether x->parent is
		 * a left or right child.  In either case, we define y to be the
		 * "uncle" of x, that is, the other child of x's grandparent.
		 *
		 * If the uncle is red, we flip the grandparent to red and its two
		 * children to black.  Then we loop around again to check whether the
		 * grandparent still has a problem.
		 *
		 * If the uncle is black, we will perform one or two "rotations" to
		 * balance the tree.  Either x or x->parent will take the
		 * grandparent's position in the tree and recolored black, and the
		 * original grandparent will be recolored red and become a child of
		 * that node. This always leaves us with a valid red-black tree, so
		 * the loop will terminate.
		 */
		if (x->parent == x->parent->parent->left)
		{
			RBTNode    *y = x->parent->parent->right;

			if (y->color == RBTRED)
			{
				/* uncle is RBTRED */
				x->parent->color = RBTBLACK;
				y->color = RBTBLACK;
				x->parent->parent->color = RBTRED;

				x = x->parent->parent;
			}
			else
			{
				/* uncle is RBTBLACK */
				if (x == x->parent->right)
				{
					/* make x a left child */
					x = x->parent;
					rbt_rotate_left(rbt, x);
				}

				/* recolor and rotate */
				x->parent->color = RBTBLACK;
				x->parent->parent->color = RBTRED;

				rbt_rotate_right(rbt, x->parent->parent);
			}
		}
		else
		{
			/* mirror image of above code */
			RBTNode    *y = x->parent->parent->left;

			if (y->color == RBTRED)
			{
				/* uncle is RBTRED */
				x->parent->color = RBTBLACK;
				y->color = RBTBLACK;
				x->parent->parent->color = RBTRED;

				x = x->parent->parent;
			}
			else
			{
				/* uncle is RBTBLACK */
				if (x == x->parent->left)
				{
					x = x->parent;
					rbt_rotate_right(rbt, x);
				}
				x->parent->color = RBTBLACK;
				x->parent->parent->color = RBTRED;

				rbt_rotate_left(rbt, x->parent->parent);
			}
		}
	}

	/*
	 * The root may already have been black; if not, the black-height of every
	 * node in the tree increases by one.
	 */
	rbt->root->color = RBTBLACK;
}