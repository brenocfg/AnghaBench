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
struct rapl_package {int /*<<< orphan*/  lead_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_PLN ; 
 int /*<<< orphan*/  X86_FEATURE_PTS ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_limit_irq_save_cpu ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rapl_package*,int) ; 

__attribute__((used)) static void package_power_limit_irq_save(struct rapl_package *rp)
{
	if (!boot_cpu_has(X86_FEATURE_PTS) || !boot_cpu_has(X86_FEATURE_PLN))
		return;

	smp_call_function_single(rp->lead_cpu, power_limit_irq_save_cpu, rp, 1);
}