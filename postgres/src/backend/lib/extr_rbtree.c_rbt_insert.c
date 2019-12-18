#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {struct TYPE_18__* right; struct TYPE_18__* left; struct TYPE_18__* parent; int /*<<< orphan*/  color; } ;
struct TYPE_17__ {int (* comparator ) (TYPE_2__ const*,TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_2__* root; int /*<<< orphan*/  arg; TYPE_2__* (* allocfunc ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* combiner ) (TYPE_2__*,TYPE_2__ const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ RBTree ;
typedef  TYPE_2__ RBTNode ;

/* Variables and functions */
 TYPE_2__* RBTNIL ; 
 int /*<<< orphan*/  RBTRED ; 
 int /*<<< orphan*/  rbt_copy_data (TYPE_1__*,TYPE_2__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  rbt_insert_fixup (TYPE_1__*,TYPE_2__*) ; 
 int stub1 (TYPE_2__ const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* stub3 (int /*<<< orphan*/ ) ; 

RBTNode *
rbt_insert(RBTree *rbt, const RBTNode *data, bool *isNew)
{
	RBTNode    *current,
			   *parent,
			   *x;
	int			cmp;

	/* find where node belongs */
	current = rbt->root;
	parent = NULL;
	cmp = 0;					/* just to prevent compiler warning */

	while (current != RBTNIL)
	{
		cmp = rbt->comparator(data, current, rbt->arg);
		if (cmp == 0)
		{
			/*
			 * Found node with given key.  Apply combiner.
			 */
			rbt->combiner(current, data, rbt->arg);
			*isNew = false;
			return current;
		}
		parent = current;
		current = (cmp < 0) ? current->left : current->right;
	}

	/*
	 * Value is not present, so create a new node containing data.
	 */
	*isNew = true;

	x = rbt->allocfunc(rbt->arg);

	x->color = RBTRED;

	x->left = RBTNIL;
	x->right = RBTNIL;
	x->parent = parent;
	rbt_copy_data(rbt, x, data);

	/* insert node in tree */
	if (parent)
	{
		if (cmp < 0)
			parent->left = x;
		else
			parent->right = x;
	}
	else
	{
		rbt->root = x;
	}

	rbt_insert_fixup(rbt, x);

	return x;
}