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
struct rq_flags {int /*<<< orphan*/  clock_update_flags; int /*<<< orphan*/  cookie; } ;
struct rq {int /*<<< orphan*/  clock_update_flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_repin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rq_repin_lock(struct rq *rq, struct rq_flags *rf)
{
	lockdep_repin_lock(&rq->lock, rf->cookie);

#ifdef CONFIG_SCHED_DEBUG
	/*
	 * Restore the value we stashed in @rf for this pin context.
	 */
	rq->clock_update_flags |= rf->clock_update_flags;
#endif
}