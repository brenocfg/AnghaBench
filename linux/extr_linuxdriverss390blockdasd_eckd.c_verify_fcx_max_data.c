#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct dasd_eckd_private {int fcx_max_data; } ;
struct dasd_device {TYPE_1__* cdev; struct dasd_eckd_private* private; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 int FCX_MAX_DATA_FACTOR ; 
 int ccw_device_get_mdc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int verify_fcx_max_data(struct dasd_device *device, __u8 lpm)
{
	struct dasd_eckd_private *private = device->private;
	int mdc;
	u32 fcx_max_data;

	if (private->fcx_max_data) {
		mdc = ccw_device_get_mdc(device->cdev, lpm);
		if ((mdc < 0)) {
			dev_warn(&device->cdev->dev,
				 "Detecting the maximum data size for zHPF "
				 "requests failed (rc=%d) for a new path %x\n",
				 mdc, lpm);
			return mdc;
		}
		fcx_max_data = (u32)mdc * FCX_MAX_DATA_FACTOR;
		if (fcx_max_data < private->fcx_max_data) {
			dev_warn(&device->cdev->dev,
				 "The maximum data size for zHPF requests %u "
				 "on a new path %x is below the active maximum "
				 "%u\n", fcx_max_data, lpm,
				 private->fcx_max_data);
			return -EACCES;
		}
	}
	return 0;
}