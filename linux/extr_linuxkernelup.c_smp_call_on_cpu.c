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
 int ENXIO ; 
 int /*<<< orphan*/  hypervisor_pin_vcpu (int) ; 

int smp_call_on_cpu(unsigned int cpu, int (*func)(void *), void *par, bool phys)
{
	int ret;

	if (cpu != 0)
		return -ENXIO;

	if (phys)
		hypervisor_pin_vcpu(0);
	ret = func(par);
	if (phys)
		hypervisor_pin_vcpu(-1);

	return ret;
}