#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct dl_rq {scalar_t__ running_bw; scalar_t__ this_bw; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHED_WARN_ON (int) ; 
 int /*<<< orphan*/  cpufreq_update_util (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 TYPE_1__* rq_of_dl_rq (struct dl_rq*) ; 

__attribute__((used)) static inline
void __add_running_bw(u64 dl_bw, struct dl_rq *dl_rq)
{
	u64 old = dl_rq->running_bw;

	lockdep_assert_held(&(rq_of_dl_rq(dl_rq))->lock);
	dl_rq->running_bw += dl_bw;
	SCHED_WARN_ON(dl_rq->running_bw < old); /* overflow */
	SCHED_WARN_ON(dl_rq->running_bw > dl_rq->this_bw);
	/* kick cpufreq (see the comment in kernel/sched/sched.h). */
	cpufreq_update_util(rq_of_dl_rq(dl_rq), 0);
}