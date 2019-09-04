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
struct usb_serial_driver {struct usb_driver* usb_driver; scalar_t__ reset_resume; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct usb_driver {char const* name; int no_dynamic_id; int supports_autosuspend; TYPE_1__ drvwrap; struct usb_device_id const* id_table; int /*<<< orphan*/  reset_resume; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  probe; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int driver_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct usb_driver*) ; 
 struct usb_driver* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_deregister (struct usb_driver*) ; 
 int usb_register (struct usb_driver*) ; 
 int /*<<< orphan*/  usb_serial_deregister (struct usb_serial_driver* const) ; 
 int /*<<< orphan*/  usb_serial_disconnect ; 
 int /*<<< orphan*/  usb_serial_probe ; 
 int usb_serial_register (struct usb_serial_driver* const) ; 
 int /*<<< orphan*/  usb_serial_reset_resume ; 
 int /*<<< orphan*/  usb_serial_resume ; 
 int /*<<< orphan*/  usb_serial_suspend ; 

int usb_serial_register_drivers(struct usb_serial_driver *const serial_drivers[],
				const char *name,
				const struct usb_device_id *id_table)
{
	int rc;
	struct usb_driver *udriver;
	struct usb_serial_driver * const *sd;

	/*
	 * udriver must be registered before any of the serial drivers,
	 * because the store_new_id() routine for the serial drivers (in
	 * bus.c) probes udriver.
	 *
	 * Performance hack: We don't want udriver to be probed until
	 * the serial drivers are registered, because the probe would
	 * simply fail for lack of a matching serial driver.
	 * So we leave udriver's id_table set to NULL until we are all set.
	 *
	 * Suspend/resume support is implemented in the usb-serial core,
	 * so fill in the PM-related fields in udriver.
	 */
	udriver = kzalloc(sizeof(*udriver), GFP_KERNEL);
	if (!udriver)
		return -ENOMEM;

	udriver->name = name;
	udriver->no_dynamic_id = 1;
	udriver->supports_autosuspend = 1;
	udriver->suspend = usb_serial_suspend;
	udriver->resume = usb_serial_resume;
	udriver->probe = usb_serial_probe;
	udriver->disconnect = usb_serial_disconnect;

	/* we only set the reset_resume field if the serial_driver has one */
	for (sd = serial_drivers; *sd; ++sd) {
		if ((*sd)->reset_resume) {
			udriver->reset_resume = usb_serial_reset_resume;
			break;
		}
	}

	rc = usb_register(udriver);
	if (rc)
		goto failed_usb_register;

	for (sd = serial_drivers; *sd; ++sd) {
		(*sd)->usb_driver = udriver;
		rc = usb_serial_register(*sd);
		if (rc)
			goto failed;
	}

	/* Now set udriver's id_table and look for matches */
	udriver->id_table = id_table;
	rc = driver_attach(&udriver->drvwrap.driver);
	return 0;

 failed:
	while (sd-- > serial_drivers)
		usb_serial_deregister(*sd);
	usb_deregister(udriver);
failed_usb_register:
	kfree(udriver);
	return rc;
}