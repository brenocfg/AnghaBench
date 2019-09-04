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
 int base_cpu ; 
 unsigned int bclk ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  outf ; 

__attribute__((used)) static void
dump_knl_turbo_ratio_limits(void)
{
	const unsigned int buckets_no = 7;

	unsigned long long msr;
	int delta_cores, delta_ratio;
	int i, b_nr;
	unsigned int cores[buckets_no];
	unsigned int ratio[buckets_no];

	get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT, &msr);

	fprintf(outf, "cpu%d: MSR_TURBO_RATIO_LIMIT: 0x%08llx\n",
		base_cpu, msr);

	/**
	 * Turbo encoding in KNL is as follows:
	 * [0] -- Reserved
	 * [7:1] -- Base value of number of active cores of bucket 1.
	 * [15:8] -- Base value of freq ratio of bucket 1.
	 * [20:16] -- +ve delta of number of active cores of bucket 2.
	 * i.e. active cores of bucket 2 =
	 * active cores of bucket 1 + delta
	 * [23:21] -- Negative delta of freq ratio of bucket 2.
	 * i.e. freq ratio of bucket 2 =
	 * freq ratio of bucket 1 - delta
	 * [28:24]-- +ve delta of number of active cores of bucket 3.
	 * [31:29]-- -ve delta of freq ratio of bucket 3.
	 * [36:32]-- +ve delta of number of active cores of bucket 4.
	 * [39:37]-- -ve delta of freq ratio of bucket 4.
	 * [44:40]-- +ve delta of number of active cores of bucket 5.
	 * [47:45]-- -ve delta of freq ratio of bucket 5.
	 * [52:48]-- +ve delta of number of active cores of bucket 6.
	 * [55:53]-- -ve delta of freq ratio of bucket 6.
	 * [60:56]-- +ve delta of number of active cores of bucket 7.
	 * [63:61]-- -ve delta of freq ratio of bucket 7.
	 */

	b_nr = 0;
	cores[b_nr] = (msr & 0xFF) >> 1;
	ratio[b_nr] = (msr >> 8) & 0xFF;

	for (i = 16; i < 64; i += 8) {
		delta_cores = (msr >> i) & 0x1F;
		delta_ratio = (msr >> (i + 5)) & 0x7;

		cores[b_nr + 1] = cores[b_nr] + delta_cores;
		ratio[b_nr + 1] = ratio[b_nr] - delta_ratio;
		b_nr++;
	}

	for (i = buckets_no - 1; i >= 0; i--)
		if (i > 0 ? ratio[i] != ratio[i - 1] : 1)
			fprintf(outf,
				"%d * %.1f = %.1f MHz max turbo %d active cores\n",
				ratio[i], bclk, ratio[i] * bclk, cores[i]);
}