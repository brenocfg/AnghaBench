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
 int bdx_highest_ratio ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

int ratio_2_msr_perf(int ratio)
{
	int msr_perf;

	if (!bdx_highest_ratio)
		return ratio;

	msr_perf = ratio * 255 / bdx_highest_ratio;

	if (debug)
		fprintf(stderr, "%d = ratio_to_msr_perf(%d)\n", msr_perf, ratio);

	return msr_perf;
}