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
struct rcu_cblist {int /*<<< orphan*/ ** tail; } ;

/* Variables and functions */
 int RCU_CBLIST_NSEGS ; 
 size_t RCU_DONE_TAIL ; 
 size_t RCU_NEXT_TAIL ; 
 int /*<<< orphan*/  rcu_segcblist_pend_cbs (struct rcu_segcblist*) ; 

void rcu_segcblist_extract_pend_cbs(struct rcu_segcblist *rsclp,
				    struct rcu_cblist *rclp)
{
	int i;

	if (!rcu_segcblist_pend_cbs(rsclp))
		return; /* Nothing to do. */
	*rclp->tail = *rsclp->tails[RCU_DONE_TAIL];
	rclp->tail = rsclp->tails[RCU_NEXT_TAIL];
	*rsclp->tails[RCU_DONE_TAIL] = NULL;
	for (i = RCU_DONE_TAIL + 1; i < RCU_CBLIST_NSEGS; i++)
		rsclp->tails[i] = rsclp->tails[RCU_DONE_TAIL];
}