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
struct dasd_device {int dummy; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
#define  CIO_BOXED 131 
#define  CIO_GONE 130 
#define  CIO_NO_PATH 129 
#define  CIO_OPER 128 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev_locked (struct ccw_device*) ; 
 int dasd_generic_last_path_gone (struct dasd_device*) ; 
 int dasd_generic_path_operational (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_get_opm (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_no_path (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 

int dasd_generic_notify(struct ccw_device *cdev, int event)
{
	struct dasd_device *device;
	int ret;

	device = dasd_device_from_cdev_locked(cdev);
	if (IS_ERR(device))
		return 0;
	ret = 0;
	switch (event) {
	case CIO_GONE:
	case CIO_BOXED:
	case CIO_NO_PATH:
		dasd_path_no_path(device);
		ret = dasd_generic_last_path_gone(device);
		break;
	case CIO_OPER:
		ret = 1;
		if (dasd_path_get_opm(device))
			ret = dasd_generic_path_operational(device);
		break;
	}
	dasd_put_device(device);
	return ret;
}