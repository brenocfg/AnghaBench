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
 int /*<<< orphan*/  MSR_TURBO_RATIO_LIMIT ; 
 int /*<<< orphan*/  MSR_TURBO_RATIO_LIMIT1 ; 
 int base_cpu ; 
 unsigned int bclk ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 scalar_t__ has_turbo_ratio_group_limits (int,int) ; 
 int /*<<< orphan*/  outf ; 

__attribute__((used)) static void
dump_turbo_ratio_limits(int family, int model)
{
	unsigned long long msr, core_counts;
	unsigned int ratio, group_size;

	get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT, &msr);
	fprintf(outf, "cpu%d: MSR_TURBO_RATIO_LIMIT: 0x%08llx\n", base_cpu, msr);

	if (has_turbo_ratio_group_limits(family, model)) {
		get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT1, &core_counts);
		fprintf(outf, "cpu%d: MSR_TURBO_RATIO_LIMIT1: 0x%08llx\n", base_cpu, core_counts);
	} else {
		core_counts = 0x0807060504030201;
	}

	ratio = (msr >> 56) & 0xFF;
	group_size = (core_counts >> 56) & 0xFF;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 48) & 0xFF;
	group_size = (core_counts >> 48) & 0xFF;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 40) & 0xFF;
	group_size = (core_counts >> 40) & 0xFF;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 32) & 0xFF;
	group_size = (core_counts >> 32) & 0xFF;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 24) & 0xFF;
	group_size = (core_counts >> 24) & 0xFF;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 16) & 0xFF;
	group_size = (core_counts >> 16) & 0xFF;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 8) & 0xFF;
	group_size = (core_counts >> 8) & 0xFF;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);

	ratio = (msr >> 0) & 0xFF;
	group_size = (core_counts >> 0) & 0xFF;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo %d active cores\n",
			ratio, bclk, ratio * bclk, group_size);
	return;
}