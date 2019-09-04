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
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct usb_driver {TYPE_1__ drvwrap; int /*<<< orphan*/ * probe; scalar_t__ no_dynamic_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_new_id ; 
 int /*<<< orphan*/  driver_attr_remove_id ; 
 int driver_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usb_create_newid_files(struct usb_driver *usb_drv)
{
	int error = 0;

	if (usb_drv->no_dynamic_id)
		goto exit;

	if (usb_drv->probe != NULL) {
		error = driver_create_file(&usb_drv->drvwrap.driver,
					   &driver_attr_new_id);
		if (error == 0) {
			error = driver_create_file(&usb_drv->drvwrap.driver,
					&driver_attr_remove_id);
			if (error)
				driver_remove_file(&usb_drv->drvwrap.driver,
						&driver_attr_new_id);
		}
	}
exit:
	return error;
}