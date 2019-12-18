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
struct sched_dl_entity {scalar_t__ dl_runtime; scalar_t__ dl_deadline; scalar_t__ dl_period; scalar_t__ flags; } ;
struct task_struct {struct sched_dl_entity dl; } ;
struct sched_attr {scalar_t__ sched_runtime; scalar_t__ sched_deadline; scalar_t__ sched_period; scalar_t__ sched_flags; } ;

/* Variables and functions */

bool dl_param_changed(struct task_struct *p, const struct sched_attr *attr)
{
	struct sched_dl_entity *dl_se = &p->dl;

	if (dl_se->dl_runtime != attr->sched_runtime ||
	    dl_se->dl_deadline != attr->sched_deadline ||
	    dl_se->dl_period != attr->sched_period ||
	    dl_se->flags != attr->sched_flags)
		return true;

	return false;
}