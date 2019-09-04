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
struct rcu_segcblist {int /*<<< orphan*/ *** tails; int /*<<< orphan*/ * head; } ;
struct rcu_cblist {int /*<<< orphan*/ * head; int /*<<< orphan*/ ** tail; } ;

/* Variables and functions */
 int RCU_CBLIST_NSEGS ; 
 int RCU_DONE_TAIL ; 

void rcu_segcblist_insert_done_cbs(struct rcu_segcblist *rsclp,
				   struct rcu_cblist *rclp)
{
	int i;

	if (!rclp->head)
		return; /* No callbacks to move. */
	*rclp->tail = rsclp->head;
	rsclp->head = rclp->head;
	for (i = RCU_DONE_TAIL; i < RCU_CBLIST_NSEGS; i++)
		if (&rsclp->head == rsclp->tails[i])
			rsclp->tails[i] = rclp->tail;
		else
			break;
	rclp->head = NULL;
	rclp->tail = &rclp->head;
}