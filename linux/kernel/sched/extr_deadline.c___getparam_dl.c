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
struct sched_dl_entity {int /*<<< orphan*/  flags; int /*<<< orphan*/  dl_period; int /*<<< orphan*/  dl_deadline; int /*<<< orphan*/  dl_runtime; } ;
struct task_struct {int /*<<< orphan*/  rt_priority; struct sched_dl_entity dl; } ;
struct sched_attr {int /*<<< orphan*/  sched_flags; int /*<<< orphan*/  sched_period; int /*<<< orphan*/  sched_deadline; int /*<<< orphan*/  sched_runtime; int /*<<< orphan*/  sched_priority; } ;

/* Variables and functions */

void __getparam_dl(struct task_struct *p, struct sched_attr *attr)
{
	struct sched_dl_entity *dl_se = &p->dl;

	attr->sched_priority = p->rt_priority;
	attr->sched_runtime = dl_se->dl_runtime;
	attr->sched_deadline = dl_se->dl_deadline;
	attr->sched_period = dl_se->dl_period;
	attr->sched_flags = dl_se->flags;
}