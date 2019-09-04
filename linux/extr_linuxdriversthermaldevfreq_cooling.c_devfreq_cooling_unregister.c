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
struct devfreq_cooling_device {struct devfreq_cooling_device* freq_table; struct devfreq_cooling_device* power_table; int /*<<< orphan*/  id; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devfreq_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct devfreq_cooling_device*) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

void devfreq_cooling_unregister(struct thermal_cooling_device *cdev)
{
	struct devfreq_cooling_device *dfc;

	if (!cdev)
		return;

	dfc = cdev->devdata;

	thermal_cooling_device_unregister(dfc->cdev);
	ida_simple_remove(&devfreq_ida, dfc->id);
	kfree(dfc->power_table);
	kfree(dfc->freq_table);

	kfree(dfc);
}