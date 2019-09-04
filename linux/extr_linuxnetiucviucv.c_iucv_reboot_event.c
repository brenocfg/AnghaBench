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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  iucv_block_cpu ; 
 int /*<<< orphan*/  iucv_disable () ; 
 int /*<<< orphan*/  iucv_irq_cpumask ; 
 int iucv_max_pathid ; 
 scalar_t__* iucv_path_table ; 
 int /*<<< orphan*/  iucv_sever_pathid (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  put_online_cpus () ; 

__attribute__((used)) static int iucv_reboot_event(struct notifier_block *this,
			     unsigned long event, void *ptr)
{
	int i;

	if (cpumask_empty(&iucv_irq_cpumask))
		return NOTIFY_DONE;

	get_online_cpus();
	on_each_cpu_mask(&iucv_irq_cpumask, iucv_block_cpu, NULL, 1);
	preempt_disable();
	for (i = 0; i < iucv_max_pathid; i++) {
		if (iucv_path_table[i])
			iucv_sever_pathid(i, NULL);
	}
	preempt_enable();
	put_online_cpus();
	iucv_disable();
	return NOTIFY_DONE;
}