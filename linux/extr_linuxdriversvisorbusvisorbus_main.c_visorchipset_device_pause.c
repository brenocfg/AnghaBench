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
struct visor_device {int pausing; } ;

/* Variables and functions */
 int visorchipset_initiate_device_pause_resume (struct visor_device*,int) ; 

int visorchipset_device_pause(struct visor_device *dev_info)
{
	int err;

	err = visorchipset_initiate_device_pause_resume(dev_info, true);
	if (err < 0) {
		dev_info->pausing = false;
		return err;
	}
	return 0;
}