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
struct TYPE_3__ {TYPE_2__* properties; } ;
struct usb_line6_podhd {TYPE_1__ line6; int /*<<< orphan*/  startup_work; int /*<<< orphan*/  startup_timer; } ;
struct usb_line6 {int /*<<< orphan*/  usbdev; } ;
struct usb_interface {int dummy; } ;
struct TYPE_4__ {int capabilities; int /*<<< orphan*/  ctrl_if; } ;

/* Variables and functions */
 int LINE6_CAP_CONTROL_INFO ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  podhd_driver ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 struct usb_interface* usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void podhd_disconnect(struct usb_line6 *line6)
{
	struct usb_line6_podhd *pod = (struct usb_line6_podhd *)line6;

	if (pod->line6.properties->capabilities & LINE6_CAP_CONTROL_INFO) {
		struct usb_interface *intf;

		del_timer_sync(&pod->startup_timer);
		cancel_work_sync(&pod->startup_work);

		intf = usb_ifnum_to_if(line6->usbdev,
					pod->line6.properties->ctrl_if);
		if (intf)
			usb_driver_release_interface(&podhd_driver, intf);
	}
}