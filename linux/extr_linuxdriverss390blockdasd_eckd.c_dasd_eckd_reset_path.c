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
struct dasd_eckd_private {scalar_t__ fcx_max_data; } ;
struct dasd_device {int /*<<< orphan*/  cdev; struct dasd_eckd_private* private; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_path_get_notoperpm (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_set_tbvpm (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ get_fcx_max_data (struct dasd_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void dasd_eckd_reset_path(struct dasd_device *device, __u8 pm)
{
	struct dasd_eckd_private *private = device->private;
	unsigned long flags;

	if (!private->fcx_max_data)
		private->fcx_max_data = get_fcx_max_data(device);
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	dasd_path_set_tbvpm(device, pm ? : dasd_path_get_notoperpm(device));
	dasd_schedule_device_bh(device);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
}