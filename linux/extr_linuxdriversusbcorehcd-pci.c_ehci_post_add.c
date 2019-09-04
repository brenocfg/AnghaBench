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
struct TYPE_2__ {struct usb_device* root_hub; struct TYPE_2__* hs_companion; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct usb_device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ is_ohci_or_uhci (struct pci_dev*) ; 
 int /*<<< orphan*/  usb_set_configuration (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

__attribute__((used)) static void ehci_post_add(struct pci_dev *pdev, struct usb_hcd *hcd,
		struct pci_dev *companion, struct usb_hcd *companion_hcd)
{
	struct usb_device *udev;

	if (is_ohci_or_uhci(companion)) {
		if (dev_get_drvdata(&pdev->dev)) {	/* Succeeded */
			dev_dbg(&pdev->dev, "HS companion for %s\n",
					dev_name(&companion->dev));
			companion_hcd->self.hs_companion = &hcd->self;
		}
		udev = companion_hcd->self.root_hub;
		usb_set_configuration(udev, 1);
		usb_unlock_device(udev);
	}
}