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
 scalar_t__ bdx_highest_ratio ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,double) ; 
 int /*<<< orphan*/  stderr ; 

int msr_perf_2_ratio(int msr_perf)
{
	int ratio;
	double d;

	if (!bdx_highest_ratio)
		return msr_perf;

	d = (double)msr_perf * (double) bdx_highest_ratio / 255.0;
	d = d + 0.5;	/* round */
	ratio = (int)d;

	if (debug)
		fprintf(stderr, "%d = msr_perf_ratio(%d) {%f}\n", ratio, msr_perf, d);

	return ratio;
}