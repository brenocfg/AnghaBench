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
struct usbatm_data {struct uea_softc* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct usb_interface {TYPE_1__ dev; } ;
struct uea_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_grp ; 
 int /*<<< orphan*/  kfree (struct uea_softc*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_stop (struct uea_softc*) ; 

__attribute__((used)) static void uea_unbind(struct usbatm_data *usbatm, struct usb_interface *intf)
{
	struct uea_softc *sc = usbatm->driver_data;

	sysfs_remove_group(&intf->dev.kobj, &attr_grp);
	uea_stop(sc);
	kfree(sc);
}