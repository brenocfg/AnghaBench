#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ root; } ;
struct TYPE_5__ {int is_over; int /*<<< orphan*/  iterate; int /*<<< orphan*/ * last_visited; TYPE_2__* rbt; } ;
typedef  TYPE_1__ RBTreeIterator ;
typedef  TYPE_2__ RBTree ;
typedef  int RBTOrderControl ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  LeftRightWalk 129 
 scalar_t__ RBTNIL ; 
#define  RightLeftWalk 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rbt_left_right_iterator ; 
 int /*<<< orphan*/  rbt_right_left_iterator ; 

void
rbt_begin_iterate(RBTree *rbt, RBTOrderControl ctrl, RBTreeIterator *iter)
{
	/* Common initialization for all traversal orders */
	iter->rbt = rbt;
	iter->last_visited = NULL;
	iter->is_over = (rbt->root == RBTNIL);

	switch (ctrl)
	{
		case LeftRightWalk:		/* visit left, then self, then right */
			iter->iterate = rbt_left_right_iterator;
			break;
		case RightLeftWalk:		/* visit right, then self, then left */
			iter->iterate = rbt_right_left_iterator;
			break;
		default:
			elog(ERROR, "unrecognized rbtree iteration order: %d", ctrl);
	}
}