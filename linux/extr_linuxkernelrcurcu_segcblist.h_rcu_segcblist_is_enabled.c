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
struct rcu_segcblist {int /*<<< orphan*/ * tails; } ;

/* Variables and functions */
 size_t RCU_NEXT_TAIL ; 

__attribute__((used)) static inline bool rcu_segcblist_is_enabled(struct rcu_segcblist *rsclp)
{
	return !!rsclp->tails[RCU_NEXT_TAIL];
}