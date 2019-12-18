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
struct rq_flags {scalar_t__ clock_update_flags; int /*<<< orphan*/  cookie; } ;
struct rq {int clock_update_flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int RQCF_ACT_SKIP ; 
 int RQCF_REQ_SKIP ; 
 int /*<<< orphan*/  lockdep_pin_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rq_pin_lock(struct rq *rq, struct rq_flags *rf)
{
	rf->cookie = lockdep_pin_lock(&rq->lock);

#ifdef CONFIG_SCHED_DEBUG
	rq->clock_update_flags &= (RQCF_REQ_SKIP|RQCF_ACT_SKIP);
	rf->clock_update_flags = 0;
#endif
}