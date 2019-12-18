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
 int EINVAL ; 
 char* _ (char*) ; 
 scalar_t__ cpufreq_get_hardware_limits (unsigned int,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  print_speed (unsigned long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int get_hardware_limits(unsigned int cpu, unsigned int human)
{
	unsigned long min, max;

	if (cpufreq_get_hardware_limits(cpu, &min, &max)) {
		printf(_("Not Available\n"));
		return -EINVAL;
	}

	if (human) {
		printf(_("  hardware limits: "));
		print_speed(min);
		printf(" - ");
		print_speed(max);
		printf("\n");
	} else {
		printf("%lu %lu\n", min, max);
	}
	return 0;
}