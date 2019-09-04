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
struct cpufreq_policy {char* governor; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int EINVAL ; 
 char* _ (char*) ; 
 struct cpufreq_policy* cpufreq_get_policy (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_put_policy (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  print_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int get_policy(unsigned int cpu)
{
	struct cpufreq_policy *policy = cpufreq_get_policy(cpu);
	if (!policy) {
		printf(_("  Unable to determine current policy\n"));
		return -EINVAL;
	}
	printf(_("  current policy: frequency should be within "));
	print_speed(policy->min);
	printf(_(" and "));
	print_speed(policy->max);

	printf(".\n                  ");
	printf(_("The governor \"%s\" may decide which speed to use\n"
	       "                  within this range.\n"),
	       policy->governor);
	cpufreq_put_policy(policy);
	return 0;
}