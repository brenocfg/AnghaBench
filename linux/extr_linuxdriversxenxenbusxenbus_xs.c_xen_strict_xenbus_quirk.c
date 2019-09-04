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

__attribute__((used)) static bool xen_strict_xenbus_quirk(void)
{
#ifdef CONFIG_X86
	uint32_t eax, ebx, ecx, edx, base;

	base = xen_cpuid_base();
	cpuid(base + 1, &eax, &ebx, &ecx, &edx);

	if ((eax >> 16) < 4)
		return true;
#endif
	return false;

}