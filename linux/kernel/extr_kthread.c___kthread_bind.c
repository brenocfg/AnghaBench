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
 int /*<<< orphan*/  __kthread_bind_mask (struct task_struct*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 

__attribute__((used)) static void __kthread_bind(struct task_struct *p, unsigned int cpu, long state)
{
	__kthread_bind_mask(p, cpumask_of(cpu), state);
}