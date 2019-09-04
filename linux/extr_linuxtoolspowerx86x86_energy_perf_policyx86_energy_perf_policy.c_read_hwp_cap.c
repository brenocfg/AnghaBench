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
struct msr_hwp_cap {void* lowest; void* efficient; void* guaranteed; void* highest; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWP_GUARANTEED_PERF (unsigned long long) ; 
 int /*<<< orphan*/  HWP_HIGHEST_PERF (unsigned long long) ; 
 int /*<<< orphan*/  HWP_LOWEST_PERF (unsigned long long) ; 
 int /*<<< orphan*/  HWP_MOSTEFFICIENT_PERF (unsigned long long) ; 
 int /*<<< orphan*/  get_msr (int,unsigned int,unsigned long long*) ; 
 void* msr_perf_2_ratio (int /*<<< orphan*/ ) ; 

void read_hwp_cap(int cpu, struct msr_hwp_cap *cap, unsigned int msr_offset)
{
	unsigned long long msr;

	get_msr(cpu, msr_offset, &msr);

	cap->highest = msr_perf_2_ratio(HWP_HIGHEST_PERF(msr));
	cap->guaranteed = msr_perf_2_ratio(HWP_GUARANTEED_PERF(msr));
	cap->efficient = msr_perf_2_ratio(HWP_MOSTEFFICIENT_PERF(msr));
	cap->lowest = msr_perf_2_ratio(HWP_LOWEST_PERF(msr));
}