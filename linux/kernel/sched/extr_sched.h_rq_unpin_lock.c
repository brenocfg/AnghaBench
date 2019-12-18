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
struct rq_flags {int /*<<< orphan*/  cookie; int /*<<< orphan*/  clock_update_flags; } ;
struct rq {scalar_t__ clock_update_flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ RQCF_ACT_SKIP ; 
 int /*<<< orphan*/  RQCF_UPDATED ; 
 int /*<<< orphan*/  lockdep_unpin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rq_unpin_lock(struct rq *rq, struct rq_flags *rf)
{
#ifdef CONFIG_SCHED_DEBUG
	if (rq->clock_update_flags > RQCF_ACT_SKIP)
		rf->clock_update_flags = RQCF_UPDATED;
#endif

	lockdep_unpin_lock(&rq->lock, rf->cookie);
}