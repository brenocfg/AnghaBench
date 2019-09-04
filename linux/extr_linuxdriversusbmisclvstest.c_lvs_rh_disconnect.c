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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct usb_interface {TYPE_1__ dev; } ;
struct lvs_rh {int /*<<< orphan*/  urb; int /*<<< orphan*/  rh_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lvs_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct lvs_rh* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lvs_rh_disconnect(struct usb_interface *intf)
{
	struct lvs_rh *lvs = usb_get_intfdata(intf);

	sysfs_remove_group(&intf->dev.kobj, &lvs_attr_group);
	usb_poison_urb(lvs->urb); /* used in scheduled work */
	flush_work(&lvs->rh_work);
	usb_free_urb(lvs->urb);
}