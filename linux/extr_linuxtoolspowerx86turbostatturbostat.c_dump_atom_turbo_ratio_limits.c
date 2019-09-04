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
 int /*<<< orphan*/  MSR_ATOM_CORE_RATIOS ; 
 int /*<<< orphan*/  MSR_ATOM_CORE_TURBO_RATIOS ; 
 int base_cpu ; 
 unsigned int bclk ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  outf ; 

__attribute__((used)) static void
dump_atom_turbo_ratio_limits(void)
{
	unsigned long long msr;
	unsigned int ratio;

	get_msr(base_cpu, MSR_ATOM_CORE_RATIOS, &msr);
	fprintf(outf, "cpu%d: MSR_ATOM_CORE_RATIOS: 0x%08llx\n", base_cpu, msr & 0xFFFFFFFF);

	ratio = (msr >> 0) & 0x3F;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz minimum operating frequency\n",
			ratio, bclk, ratio * bclk);

	ratio = (msr >> 8) & 0x3F;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz low frequency mode (LFM)\n",
			ratio, bclk, ratio * bclk);

	ratio = (msr >> 16) & 0x3F;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz base frequency\n",
			ratio, bclk, ratio * bclk);

	get_msr(base_cpu, MSR_ATOM_CORE_TURBO_RATIOS, &msr);
	fprintf(outf, "cpu%d: MSR_ATOM_CORE_TURBO_RATIOS: 0x%08llx\n", base_cpu, msr & 0xFFFFFFFF);

	ratio = (msr >> 24) & 0x3F;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo 4 active cores\n",
			ratio, bclk, ratio * bclk);

	ratio = (msr >> 16) & 0x3F;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo 3 active cores\n",
			ratio, bclk, ratio * bclk);

	ratio = (msr >> 8) & 0x3F;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo 2 active cores\n",
			ratio, bclk, ratio * bclk);

	ratio = (msr >> 0) & 0x3F;
	if (ratio)
		fprintf(outf, "%d * %.1f = %.1f MHz max turbo 1 active core\n",
			ratio, bclk, ratio * bclk);
}