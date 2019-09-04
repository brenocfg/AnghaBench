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
struct sched_dl_entity {int /*<<< orphan*/  dl_runtime; int /*<<< orphan*/  dl_deadline; void* dl_density; int /*<<< orphan*/  dl_period; void* dl_bw; int /*<<< orphan*/  flags; } ;
struct task_struct {struct sched_dl_entity dl; } ;
struct sched_attr {int /*<<< orphan*/  sched_flags; scalar_t__ sched_period; int /*<<< orphan*/  sched_deadline; int /*<<< orphan*/  sched_runtime; } ;

/* Variables and functions */
 void* to_ratio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __setparam_dl(struct task_struct *p, const struct sched_attr *attr)
{
	struct sched_dl_entity *dl_se = &p->dl;

	dl_se->dl_runtime = attr->sched_runtime;
	dl_se->dl_deadline = attr->sched_deadline;
	dl_se->dl_period = attr->sched_period ?: dl_se->dl_deadline;
	dl_se->flags = attr->sched_flags;
	dl_se->dl_bw = to_ratio(dl_se->dl_period, dl_se->dl_runtime);
	dl_se->dl_density = to_ratio(dl_se->dl_deadline, dl_se->dl_runtime);
}