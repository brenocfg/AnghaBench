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
 unsigned long cpufreq_get_freq_hardware (unsigned int) ; 
 int /*<<< orphan*/  print_speed (unsigned long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int get_freq_hardware(unsigned int cpu, unsigned int human)
{
	unsigned long freq = cpufreq_get_freq_hardware(cpu);
	printf(_("  current CPU frequency: "));
	if (!freq) {
		printf("Unable to call hardware\n");
		return -EINVAL;
	}
	if (human) {
		print_speed(freq);
	} else
		printf("%lu", freq);
	printf(_(" (asserted by call to hardware)\n"));
	return 0;
}