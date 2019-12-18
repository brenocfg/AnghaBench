#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* parent; struct TYPE_7__* left; struct TYPE_7__* right; } ;
struct TYPE_6__ {TYPE_2__* root; } ;
typedef  TYPE_1__ RBTree ;
typedef  TYPE_2__ RBTNode ;

/* Variables and functions */
 TYPE_2__* RBTNIL ; 

__attribute__((used)) static void
rbt_rotate_left(RBTree *rbt, RBTNode *x)
{
	RBTNode    *y = x->right;

	/* establish x->right link */
	x->right = y->left;
	if (y->left != RBTNIL)
		y->left->parent = x;

	/* establish y->parent link */
	if (y != RBTNIL)
		y->parent = x->parent;
	if (x->parent)
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else
	{
		rbt->root = y;
	}

	/* link x and y */
	y->left = x;
	if (x != RBTNIL)
		x->parent = y;
}