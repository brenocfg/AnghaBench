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
 int /*<<< orphan*/  __cpuid (int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 unsigned int cpu_model ; 

__attribute__((used)) static void update_cpu_model(void)
{
	unsigned int ebx, ecx, edx;
	unsigned int fms, family;

	__cpuid(1, fms, ebx, ecx, edx);
	family = (fms >> 8) & 0xf;
	cpu_model = (fms >> 4) & 0xf;
	if (family == 6 || family == 0xf)
		cpu_model += ((fms >> 16) & 0xf) << 4;
}