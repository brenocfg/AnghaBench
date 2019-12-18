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
 int /*<<< orphan*/  CPU_PROFILING ; 
 int /*<<< orphan*/  KVM_PROFILING ; 
 int /*<<< orphan*/  SCHED_PROFILING ; 
 int /*<<< orphan*/  SLEEP_PROFILING ; 
 int /*<<< orphan*/  force_schedstat_enabled () ; 
 scalar_t__ get_option (char**,int*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  prof_on ; 
 int prof_shift ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

int profile_setup(char *str)
{
	static const char schedstr[] = "schedule";
	static const char sleepstr[] = "sleep";
	static const char kvmstr[] = "kvm";
	int par;

	if (!strncmp(str, sleepstr, strlen(sleepstr))) {
#ifdef CONFIG_SCHEDSTATS
		force_schedstat_enabled();
		prof_on = SLEEP_PROFILING;
		if (str[strlen(sleepstr)] == ',')
			str += strlen(sleepstr) + 1;
		if (get_option(&str, &par))
			prof_shift = par;
		pr_info("kernel sleep profiling enabled (shift: %ld)\n",
			prof_shift);
#else
		pr_warn("kernel sleep profiling requires CONFIG_SCHEDSTATS\n");
#endif /* CONFIG_SCHEDSTATS */
	} else if (!strncmp(str, schedstr, strlen(schedstr))) {
		prof_on = SCHED_PROFILING;
		if (str[strlen(schedstr)] == ',')
			str += strlen(schedstr) + 1;
		if (get_option(&str, &par))
			prof_shift = par;
		pr_info("kernel schedule profiling enabled (shift: %ld)\n",
			prof_shift);
	} else if (!strncmp(str, kvmstr, strlen(kvmstr))) {
		prof_on = KVM_PROFILING;
		if (str[strlen(kvmstr)] == ',')
			str += strlen(kvmstr) + 1;
		if (get_option(&str, &par))
			prof_shift = par;
		pr_info("kernel KVM profiling enabled (shift: %ld)\n",
			prof_shift);
	} else if (get_option(&str, &par)) {
		prof_shift = par;
		prof_on = CPU_PROFILING;
		pr_info("kernel profiling enabled (shift: %ld)\n",
			prof_shift);
	}
	return 1;
}