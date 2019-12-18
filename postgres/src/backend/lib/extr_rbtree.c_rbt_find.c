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
struct TYPE_10__ {struct TYPE_10__* right; struct TYPE_10__* left; } ;
struct TYPE_9__ {int (* comparator ) (TYPE_2__ const*,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  arg; TYPE_2__* root; } ;
typedef  TYPE_1__ RBTree ;
typedef  TYPE_2__ RBTNode ;

/* Variables and functions */
 TYPE_2__* RBTNIL ; 
 int stub1 (TYPE_2__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 

RBTNode *
rbt_find(RBTree *rbt, const RBTNode *data)
{
	RBTNode    *node = rbt->root;

	while (node != RBTNIL)
	{
		int			cmp = rbt->comparator(data, node, rbt->arg);

		if (cmp == 0)
			return node;
		else if (cmp < 0)
			node = node->left;
		else
			node = node->right;
	}

	return NULL;
}