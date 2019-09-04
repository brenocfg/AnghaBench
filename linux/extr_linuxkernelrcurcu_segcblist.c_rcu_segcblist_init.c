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
struct rcu_segcblist {scalar_t__ len_lazy; scalar_t__ len; int /*<<< orphan*/ * head; int /*<<< orphan*/ *** tails; int /*<<< orphan*/ *** gp_seq; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int RCU_CBLIST_NSEGS ; 
 scalar_t__ RCU_NEXT_TAIL ; 

void rcu_segcblist_init(struct rcu_segcblist *rsclp)
{
	int i;

	BUILD_BUG_ON(RCU_NEXT_TAIL + 1 != ARRAY_SIZE(rsclp->gp_seq));
	BUILD_BUG_ON(ARRAY_SIZE(rsclp->tails) != ARRAY_SIZE(rsclp->gp_seq));
	rsclp->head = NULL;
	for (i = 0; i < RCU_CBLIST_NSEGS; i++)
		rsclp->tails[i] = &rsclp->head;
	rsclp->len = 0;
	rsclp->len_lazy = 0;
}