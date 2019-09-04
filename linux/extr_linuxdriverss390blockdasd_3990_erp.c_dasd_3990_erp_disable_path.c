#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dasd_device {int features; TYPE_2__* path; TYPE_1__* cdev; } ;
typedef  int __u8 ;
struct TYPE_4__ {int /*<<< orphan*/  error_count; scalar_t__ errorclk; int /*<<< orphan*/  chpid; int /*<<< orphan*/  cssid; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DASD_FEATURE_PATH_AUTODISABLE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_path_add_ifccpm (struct dasd_device*,int) ; 
 int dasd_path_get_opm (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_remove_opm (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pathmask_to_pos (int) ; 

__attribute__((used)) static void dasd_3990_erp_disable_path(struct dasd_device *device, __u8 lpum)
{
	int pos = pathmask_to_pos(lpum);

	if (!(device->features & DASD_FEATURE_PATH_AUTODISABLE)) {
		dev_err(&device->cdev->dev,
			"Path %x.%02x (pathmask %02x) is operational despite excessive IFCCs\n",
			device->path[pos].cssid, device->path[pos].chpid, lpum);
		goto out;
	}

	/* no remaining path, cannot disable */
	if (!(dasd_path_get_opm(device) & ~lpum)) {
		dev_err(&device->cdev->dev,
			"Last path %x.%02x (pathmask %02x) is operational despite excessive IFCCs\n",
			device->path[pos].cssid, device->path[pos].chpid, lpum);
		goto out;
	}

	dev_err(&device->cdev->dev,
		"Path %x.%02x (pathmask %02x) is disabled - IFCC threshold exceeded\n",
		device->path[pos].cssid, device->path[pos].chpid, lpum);
	dasd_path_remove_opm(device, lpum);
	dasd_path_add_ifccpm(device, lpum);

out:
	device->path[pos].errorclk = 0;
	atomic_set(&device->path[pos].error_count, 0);
}