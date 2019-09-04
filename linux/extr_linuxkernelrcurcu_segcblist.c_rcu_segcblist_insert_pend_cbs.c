#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rcu_segcblist {int /*<<< orphan*/ *** tails; } ;
struct rcu_cblist {int /*<<< orphan*/ * head; int /*<<< orphan*/ ** tail; } ;

/* Variables and functions */
 size_t RCU_NEXT_TAIL ; 

void rcu_segcblist_insert_pend_cbs(struct rcu_segcblist *rsclp,
				   struct rcu_cblist *rclp)
{
	if (!rclp->head)
		return; /* Nothing to do. */
	*rsclp->tails[RCU_NEXT_TAIL] = rclp->head;
	rsclp->tails[RCU_NEXT_TAIL] = rclp->tail;
	rclp->head = NULL;
	rclp->tail = &rclp->head;
}