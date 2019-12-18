#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* right; struct TYPE_9__* parent; struct TYPE_9__* left; } ;
struct TYPE_8__ {int is_over; TYPE_3__* last_visited; TYPE_1__* rbt; } ;
struct TYPE_7__ {TYPE_3__* root; } ;
typedef  TYPE_2__ RBTreeIterator ;
typedef  TYPE_3__ RBTNode ;

/* Variables and functions */
 TYPE_3__* RBTNIL ; 

__attribute__((used)) static RBTNode *
rbt_right_left_iterator(RBTreeIterator *iter)
{
	if (iter->last_visited == NULL)
	{
		iter->last_visited = iter->rbt->root;
		while (iter->last_visited->right != RBTNIL)
			iter->last_visited = iter->last_visited->right;

		return iter->last_visited;
	}

	if (iter->last_visited->left != RBTNIL)
	{
		iter->last_visited = iter->last_visited->left;
		while (iter->last_visited->right != RBTNIL)
			iter->last_visited = iter->last_visited->right;

		return iter->last_visited;
	}

	for (;;)
	{
		RBTNode    *came_from = iter->last_visited;

		iter->last_visited = iter->last_visited->parent;
		if (iter->last_visited == NULL)
		{
			iter->is_over = true;
			break;
		}

		if (iter->last_visited->right == came_from)
			break;				/* came from right sub-tree, return current
								 * node */

		/* else - came from left sub-tree, continue to move up */
	}

	return iter->last_visited;
}