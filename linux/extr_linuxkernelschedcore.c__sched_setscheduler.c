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
struct task_struct {int /*<<< orphan*/  static_prio; } ;
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
struct sched_attr {int sched_policy; int /*<<< orphan*/  sched_flags; int /*<<< orphan*/  sched_nice; int /*<<< orphan*/  sched_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIO_TO_NICE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCHED_FLAG_RESET_ON_FORK ; 
 int SCHED_RESET_ON_FORK ; 
 int SETPARAM_POLICY ; 
 int __sched_setscheduler (struct task_struct*,struct sched_attr*,int,int) ; 

__attribute__((used)) static int _sched_setscheduler(struct task_struct *p, int policy,
			       const struct sched_param *param, bool check)
{
	struct sched_attr attr = {
		.sched_policy   = policy,
		.sched_priority = param->sched_priority,
		.sched_nice	= PRIO_TO_NICE(p->static_prio),
	};

	/* Fixup the legacy SCHED_RESET_ON_FORK hack. */
	if ((policy != SETPARAM_POLICY) && (policy & SCHED_RESET_ON_FORK)) {
		attr.sched_flags |= SCHED_FLAG_RESET_ON_FORK;
		policy &= ~SCHED_RESET_ON_FORK;
		attr.sched_policy = policy;
	}

	return __sched_setscheduler(p, &attr, check, true);
}