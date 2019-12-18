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
struct cgroup {int dummy; } ;

/* Variables and functions */
 int __cgroup_task_count (struct cgroup const*) ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int cgroup_task_count(const struct cgroup *cgrp)
{
	int count;

	spin_lock_irq(&css_set_lock);
	count = __cgroup_task_count(cgrp);
	spin_unlock_irq(&css_set_lock);

	return count;
}