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
struct cpufreq_available_governors {char* governor; struct cpufreq_available_governors* next; } ;

/* Variables and functions */
 int EINVAL ; 
 char* _ (char*) ; 
 struct cpufreq_available_governors* cpufreq_get_available_governors (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_put_available_governors (struct cpufreq_available_governors*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int get_available_governors(unsigned int cpu)
{
	struct cpufreq_available_governors *governors =
		cpufreq_get_available_governors(cpu);

	printf(_("  available cpufreq governors: "));
	if (!governors) {
		printf(_("Not Available\n"));
		return -EINVAL;
	}

	while (governors->next) {
		printf("%s ", governors->governor);
		governors = governors->next;
	}
	printf("%s\n", governors->governor);
	cpufreq_put_available_governors(governors);
	return 0;
}