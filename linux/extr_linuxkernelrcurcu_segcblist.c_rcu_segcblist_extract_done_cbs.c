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
struct rcu_segcblist {int /*<<< orphan*/ * head; int /*<<< orphan*/ *** tails; } ;
struct rcu_cblist {int /*<<< orphan*/ ** tail; } ;

/* Variables and functions */
 int RCU_CBLIST_NSEGS ; 
 size_t RCU_DONE_TAIL ; 
 int /*<<< orphan*/  rcu_segcblist_ready_cbs (struct rcu_segcblist*) ; 

void rcu_segcblist_extract_done_cbs(struct rcu_segcblist *rsclp,
				    struct rcu_cblist *rclp)
{
	int i;

	if (!rcu_segcblist_ready_cbs(rsclp))
		return; /* Nothing to do. */
	*rclp->tail = rsclp->head;
	rsclp->head = *rsclp->tails[RCU_DONE_TAIL];
	*rsclp->tails[RCU_DONE_TAIL] = NULL;
	rclp->tail = rsclp->tails[RCU_DONE_TAIL];
	for (i = RCU_CBLIST_NSEGS - 1; i >= RCU_DONE_TAIL; i--)
		if (rsclp->tails[i] == rsclp->tails[RCU_DONE_TAIL])
			rsclp->tails[i] = &rsclp->head;
}