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
 int /*<<< orphan*/  MSR_APERF ; 
 int /*<<< orphan*/  MSR_MPERF ; 
 unsigned long long* aperf_previous_count ; 
 int* is_valid ; 
 unsigned long long* mperf_previous_count ; 
 int read_msr (unsigned int,int /*<<< orphan*/ ,unsigned long long*) ; 

__attribute__((used)) static int mperf_init_stats(unsigned int cpu)
{
	unsigned long long val;
	int ret;

	ret = read_msr(cpu, MSR_APERF, &val);
	aperf_previous_count[cpu] = val;
	ret |= read_msr(cpu, MSR_MPERF, &val);
	mperf_previous_count[cpu] = val;
	is_valid[cpu] = !ret;

	return 0;
}