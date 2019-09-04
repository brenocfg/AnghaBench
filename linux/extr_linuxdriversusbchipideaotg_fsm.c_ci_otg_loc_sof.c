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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct otg_fsm {TYPE_2__* otg; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  root_hub; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_disable_autosuspend (struct usb_device*) ; 
 int /*<<< orphan*/  usb_enable_autosuspend (struct usb_device*) ; 
 struct usb_device* usb_hub_find_child (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ci_otg_loc_sof(struct otg_fsm *fsm, int on)
{
	struct usb_device *udev;

	if (!fsm->otg->host)
		return;

	udev = usb_hub_find_child(fsm->otg->host->root_hub, 1);
	if (!udev)
		return;

	if (on) {
		usb_disable_autosuspend(udev);
	} else {
		pm_runtime_set_autosuspend_delay(&udev->dev, 0);
		usb_enable_autosuspend(udev);
	}
}