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
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct usb_bus {scalar_t__ root_hub; } ;
struct gb_usb_device {TYPE_1__* gbphy_dev; int /*<<< orphan*/  connection; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_USB_TYPE_HCD_START ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_bus* hcd_to_bus (struct usb_hcd*) ; 
 struct gb_usb_device* to_gb_usb_device (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 

__attribute__((used)) static int hcd_start(struct usb_hcd *hcd)
{
	struct usb_bus *bus = hcd_to_bus(hcd);
	struct gb_usb_device *dev = to_gb_usb_device(hcd);
	int ret;

	ret = gb_operation_sync(dev->connection, GB_USB_TYPE_HCD_START,
				NULL, 0, NULL, 0);
	if (ret) {
		dev_err(&dev->gbphy_dev->dev, "HCD start failed '%d'\n", ret);
		return ret;
	}

	hcd->state = HC_STATE_RUNNING;
	if (bus->root_hub)
		usb_hcd_resume_root_hub(hcd);
	return 0;
}