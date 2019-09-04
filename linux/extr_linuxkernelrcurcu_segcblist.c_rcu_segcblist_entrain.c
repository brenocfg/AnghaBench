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
 int RCU_DONE_TAIL ; 
 int RCU_NEXT_TAIL ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 scalar_t__ rcu_segcblist_n_cbs (struct rcu_segcblist*) ; 
 int /*<<< orphan*/  smp_mb () ; 

bool rcu_segcblist_entrain(struct rcu_segcblist *rsclp,
			   struct rcu_head *rhp, bool lazy)
{
	int i;

	if (rcu_segcblist_n_cbs(rsclp) == 0)
		return false;
	WRITE_ONCE(rsclp->len, rsclp->len + 1);
	if (lazy)
		rsclp->len_lazy++;
	smp_mb(); /* Ensure counts are updated before callback is entrained. */
	rhp->next = NULL;
	for (i = RCU_NEXT_TAIL; i > RCU_DONE_TAIL; i--)
		if (rsclp->tails[i] != rsclp->tails[i - 1])
			break;
	*rsclp->tails[i] = rhp;
	for (; i <= RCU_NEXT_TAIL; i++)
		rsclp->tails[i] = &rhp->next;
	return true;
}