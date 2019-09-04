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
struct rcu_segcblist {struct rcu_head*** tails; } ;
struct rcu_head {int dummy; } ;

/* Variables and functions */
 size_t RCU_NEXT_TAIL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_segcblist_empty (struct rcu_segcblist*) ; 

__attribute__((used)) static inline struct rcu_head **rcu_segcblist_tail(struct rcu_segcblist *rsclp)
{
	WARN_ON_ONCE(rcu_segcblist_empty(rsclp));
	return rsclp->tails[RCU_NEXT_TAIL];
}