#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuidle_monitor {int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; } ;
struct TYPE_2__ {int caps; } ;

/* Variables and functions */
 int CPUPOWER_CAP_APERF ; 
 void* aperf_current_count ; 
 void* aperf_previous_count ; 
 void* calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_count ; 
 TYPE_1__ cpupower_cpu_info ; 
 scalar_t__ init_maxfreq_mode () ; 
 void* is_valid ; 
 void* mperf_current_count ; 
 struct cpuidle_monitor mperf_monitor ; 
 void* mperf_previous_count ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

struct cpuidle_monitor *mperf_register(void)
{
	if (!(cpupower_cpu_info.caps & CPUPOWER_CAP_APERF))
		return NULL;

	if (init_maxfreq_mode())
		return NULL;

	/* Free this at program termination */
	is_valid = calloc(cpu_count, sizeof(int));
	mperf_previous_count = calloc(cpu_count, sizeof(unsigned long long));
	aperf_previous_count = calloc(cpu_count, sizeof(unsigned long long));
	mperf_current_count = calloc(cpu_count, sizeof(unsigned long long));
	aperf_current_count = calloc(cpu_count, sizeof(unsigned long long));

	mperf_monitor.name_len = strlen(mperf_monitor.name);
	return &mperf_monitor;
}