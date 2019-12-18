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
 int /*<<< orphan*/  MSR_FSB_FREQ ; 
 unsigned int SLM_BCLK_FREQS ; 
 int /*<<< orphan*/  base_cpu ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  quiet ; 
 double* slm_freq_table ; 

double slm_bclk(void)
{
	unsigned long long msr = 3;
	unsigned int i;
	double freq;

	if (get_msr(base_cpu, MSR_FSB_FREQ, &msr))
		fprintf(outf, "SLM BCLK: unknown\n");

	i = msr & 0xf;
	if (i >= SLM_BCLK_FREQS) {
		fprintf(outf, "SLM BCLK[%d] invalid\n", i);
		i = 3;
	}
	freq = slm_freq_table[i];

	if (!quiet)
		fprintf(outf, "SLM BCLK: %.1f Mhz\n", freq);

	return freq;
}