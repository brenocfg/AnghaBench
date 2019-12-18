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
 char* cpufreq_get_driver (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_put_driver (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int get_driver(unsigned int cpu)
{
	char *driver = cpufreq_get_driver(cpu);
	if (!driver) {
		printf(_("  no or unknown cpufreq driver is active on this CPU\n"));
		return -EINVAL;
	}
	printf("  driver: %s\n", driver);
	cpufreq_put_driver(driver);
	return 0;
}