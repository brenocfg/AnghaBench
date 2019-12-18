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
struct TYPE_7__ {struct TYPE_7__* parent; struct TYPE_7__* right; struct TYPE_7__* left; } ;
struct TYPE_6__ {TYPE_2__* root; } ;
typedef  TYPE_1__ RBTree ;
typedef  TYPE_2__ RBTNode ;

/* Variables and functions */
 TYPE_2__* RBTNIL ; 

__attribute__((used)) static void
rbt_rotate_right(RBTree *rbt, RBTNode *x)
{
	RBTNode    *y = x->left;

	/* establish x->left link */
	x->left = y->right;
	if (y->right != RBTNIL)
		y->right->parent = x;

	/* establish y->parent link */
	if (y != RBTNIL)
		y->parent = x->parent;
	if (x->parent)
	{
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else
	{
		rbt->root = y;
	}

	/* link x and y */
	y->right = x;
	if (x != RBTNIL)
		x->parent = y;
}