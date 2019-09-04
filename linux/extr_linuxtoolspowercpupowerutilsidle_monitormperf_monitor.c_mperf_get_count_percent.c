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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int C0 ; 
 unsigned int Cx ; 
 scalar_t__ MAX_FREQ_SYSFS ; 
 scalar_t__ MAX_FREQ_TSC_REF ; 
 unsigned long long* aperf_current_count ; 
 unsigned long long* aperf_previous_count ; 
 int /*<<< orphan*/  dprint (char*,int /*<<< orphan*/ ,double,...) ; 
 int /*<<< orphan*/ * is_valid ; 
 scalar_t__ max_freq_mode ; 
 unsigned long long max_frequency ; 
 TYPE_1__* mperf_cstates ; 
 unsigned long long* mperf_current_count ; 
 unsigned long long* mperf_previous_count ; 
 int /*<<< orphan*/  time_end ; 
 int /*<<< orphan*/  time_start ; 
 unsigned long long timespec_diff_us (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long tsc_at_measure_end ; 
 unsigned long long tsc_at_measure_start ; 

__attribute__((used)) static int mperf_get_count_percent(unsigned int id, double *percent,
				   unsigned int cpu)
{
	unsigned long long aperf_diff, mperf_diff, tsc_diff;
	unsigned long long timediff;

	if (!is_valid[cpu])
		return -1;

	if (id != C0 && id != Cx)
		return -1;

	mperf_diff = mperf_current_count[cpu] - mperf_previous_count[cpu];
	aperf_diff = aperf_current_count[cpu] - aperf_previous_count[cpu];

	if (max_freq_mode == MAX_FREQ_TSC_REF) {
		tsc_diff = tsc_at_measure_end - tsc_at_measure_start;
		*percent = 100.0 * mperf_diff / tsc_diff;
		dprint("%s: TSC Ref - mperf_diff: %llu, tsc_diff: %llu\n",
		       mperf_cstates[id].name, mperf_diff, tsc_diff);
	} else if (max_freq_mode == MAX_FREQ_SYSFS) {
		timediff = max_frequency * timespec_diff_us(time_start, time_end);
		*percent = 100.0 * mperf_diff / timediff;
		dprint("%s: MAXFREQ - mperf_diff: %llu, time_diff: %llu\n",
		       mperf_cstates[id].name, mperf_diff, timediff);
	} else
		return -1;

	if (id == Cx)
		*percent = 100.0 - *percent;

	dprint("%s: previous: %llu - current: %llu - (%u)\n",
		mperf_cstates[id].name, mperf_diff, aperf_diff, cpu);
	dprint("%s: %f\n", mperf_cstates[id].name, *percent);
	return 0;
}