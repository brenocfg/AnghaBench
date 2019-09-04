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
struct ab8500_fg_avg_cap {scalar_t__* time_stamps; scalar_t__* samples; int /*<<< orphan*/  avg; scalar_t__ sum; scalar_t__ nbr_samples; scalar_t__ pos; } ;
struct ab8500_fg {struct ab8500_fg_avg_cap avg_cap; } ;

/* Variables and functions */
 int NBR_AVG_SAMPLES ; 

__attribute__((used)) static void ab8500_fg_clear_cap_samples(struct ab8500_fg *di)
{
	int i;
	struct ab8500_fg_avg_cap *avg = &di->avg_cap;

	avg->pos = 0;
	avg->nbr_samples = 0;
	avg->sum = 0;
	avg->avg = 0;

	for (i = 0; i < NBR_AVG_SAMPLES; i++) {
		avg->samples[i] = 0;
		avg->time_stamps[i] = 0;
	}
}