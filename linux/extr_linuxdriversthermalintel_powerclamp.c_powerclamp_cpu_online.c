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
 int clamping ; 
 scalar_t__ control_cpu ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  start_power_clamp_worker (unsigned int) ; 

__attribute__((used)) static int powerclamp_cpu_online(unsigned int cpu)
{
	if (clamping == false)
		return 0;
	start_power_clamp_worker(cpu);
	/* prefer BSP as controlling CPU */
	if (cpu == 0) {
		control_cpu = 0;
		smp_mb();
	}
	return 0;
}