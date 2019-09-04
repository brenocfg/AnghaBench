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
struct rcu_segcblist {struct rcu_head*** tails; int /*<<< orphan*/  len_lazy; scalar_t__ len; } ;
struct rcu_head {struct rcu_head* next; } ;

/* Variables and functions */
 size_t RCU_NEXT_TAIL ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  smp_mb () ; 

void rcu_segcblist_enqueue(struct rcu_segcblist *rsclp,
			   struct rcu_head *rhp, bool lazy)
{
	WRITE_ONCE(rsclp->len, rsclp->len + 1); /* ->len sampled locklessly. */
	if (lazy)
		rsclp->len_lazy++;
	smp_mb(); /* Ensure counts are updated before callback is enqueued. */
	rhp->next = NULL;
	*rsclp->tails[RCU_NEXT_TAIL] = rhp;
	rsclp->tails[RCU_NEXT_TAIL] = &rhp->next;
}