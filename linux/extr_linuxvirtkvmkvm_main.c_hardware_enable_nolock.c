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

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_hardware_enabled ; 
 int /*<<< orphan*/  hardware_enable_failed ; 
 int kvm_arch_hardware_enable () ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int raw_smp_processor_id () ; 

__attribute__((used)) static void hardware_enable_nolock(void *junk)
{
	int cpu = raw_smp_processor_id();
	int r;

	if (cpumask_test_cpu(cpu, cpus_hardware_enabled))
		return;

	cpumask_set_cpu(cpu, cpus_hardware_enabled);

	r = kvm_arch_hardware_enable();

	if (r) {
		cpumask_clear_cpu(cpu, cpus_hardware_enabled);
		atomic_inc(&hardware_enable_failed);
		pr_info("kvm: enabling virtualization on CPU%d failed\n", cpu);
	}
}