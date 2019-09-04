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
struct thermal_cooling_device {struct devfreq_cooling_device* devdata; } ;
struct devfreq_cooling_device {int freq_table_size; } ;

/* Variables and functions */

__attribute__((used)) static int devfreq_cooling_get_max_state(struct thermal_cooling_device *cdev,
					 unsigned long *state)
{
	struct devfreq_cooling_device *dfc = cdev->devdata;

	*state = dfc->freq_table_size - 1;

	return 0;
}