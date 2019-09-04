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
struct usb_hcd {int amd_resume_bug; } ;
struct usb_device {int level; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_amd_resume_quirk(struct usb_device *udev)
{
	struct usb_hcd *hcd;

	hcd = bus_to_hcd(udev->bus);
	/* The device should be attached directly to root hub */
	if (udev->level == 1 && hcd->amd_resume_bug == 1)
		return 1;

	return 0;
}