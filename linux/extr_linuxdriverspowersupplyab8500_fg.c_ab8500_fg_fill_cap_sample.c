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
typedef  int /*<<< orphan*/  time64_t ;
struct ab8500_fg_avg_cap {int* samples; int nbr_samples; int sum; int avg; scalar_t__ pos; int /*<<< orphan*/ * time_stamps; } ;
struct ab8500_fg {struct ab8500_fg_avg_cap avg_cap; } ;

/* Variables and functions */
 int NBR_AVG_SAMPLES ; 
 int /*<<< orphan*/  ktime_get_boottime_seconds () ; 

__attribute__((used)) static void ab8500_fg_fill_cap_sample(struct ab8500_fg *di, int sample)
{
	int i;
	time64_t now;
	struct ab8500_fg_avg_cap *avg = &di->avg_cap;

	now = ktime_get_boottime_seconds();

	for (i = 0; i < NBR_AVG_SAMPLES; i++) {
		avg->samples[i] = sample;
		avg->time_stamps[i] = now;
	}

	avg->pos = 0;
	avg->nbr_samples = NBR_AVG_SAMPLES;
	avg->sum = sample * NBR_AVG_SAMPLES;
	avg->avg = sample;
}