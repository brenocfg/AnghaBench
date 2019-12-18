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
struct sched_avg {int dummy; } ;
struct cfs_rq {struct sched_avg const avg; } ;

/* Variables and functions */

const struct sched_avg *sched_trace_cfs_rq_avg(struct cfs_rq *cfs_rq)
{
#ifdef CONFIG_SMP
	return cfs_rq ? &cfs_rq->avg : NULL;
#else
	return NULL;
#endif
}