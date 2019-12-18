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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __kthread_bind_mask (struct task_struct*,struct cpumask const*,int /*<<< orphan*/ ) ; 

void kthread_bind_mask(struct task_struct *p, const struct cpumask *mask)
{
	__kthread_bind_mask(p, mask, TASK_UNINTERRUPTIBLE);
}