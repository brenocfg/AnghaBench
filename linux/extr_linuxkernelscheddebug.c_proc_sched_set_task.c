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
struct task_struct {int dummy; } ;

/* Variables and functions */

void proc_sched_set_task(struct task_struct *p)
{
#ifdef CONFIG_SCHEDSTATS
	memset(&p->se.statistics, 0, sizeof(p->se.statistics));
#endif
}