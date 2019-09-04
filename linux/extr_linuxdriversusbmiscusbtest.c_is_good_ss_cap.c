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
typedef  int /*<<< orphan*/  u8 ;
struct usbtest_dev {int dummy; } ;
struct usb_ss_cap_descriptor {scalar_t__ bLength; int bmAttributes; int /*<<< orphan*/  wSpeedSupported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct usbtest_dev*,char*) ; 
 scalar_t__ USB_DT_USB_SS_CAP_SIZE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_good_ss_cap(struct usbtest_dev *tdev, u8 *buf)
{
	struct usb_ss_cap_descriptor *ss;

	ss = (struct usb_ss_cap_descriptor *) buf;

	if (ss->bLength != USB_DT_USB_SS_CAP_SIZE) {
		ERROR(tdev, "bogus superspeed device capability descriptor length\n");
		return 0;
	}

	/*
	 * only bit[1] of bmAttributes is used for LTM and others are
	 * reserved
	 */
	if (ss->bmAttributes & ~0x02) {	/* reserved == 0 */
		ERROR(tdev, "reserved bits set in bmAttributes\n");
		return 0;
	}

	/* bits[0:3] of wSpeedSupported is used and others are reserved */
	if (le16_to_cpu(ss->wSpeedSupported) & ~0x0f) {	/* reserved == 0 */
		ERROR(tdev, "reserved bits set in wSpeedSupported\n");
		return 0;
	}

	return 1;
}