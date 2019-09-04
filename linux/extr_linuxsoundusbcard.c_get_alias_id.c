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
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_ID_PRODUCT (unsigned int) ; 
 int /*<<< orphan*/  USB_ID_VENDOR (unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * quirk_alias ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static bool get_alias_id(struct usb_device *dev, unsigned int *id)
{
	int i;
	unsigned int src, dst;

	for (i = 0; i < ARRAY_SIZE(quirk_alias); i++) {
		if (!quirk_alias[i] ||
		    sscanf(quirk_alias[i], "%x:%x", &src, &dst) != 2 ||
		    src != *id)
			continue;
		dev_info(&dev->dev,
			 "device (%04x:%04x): applying quirk alias %04x:%04x\n",
			 USB_ID_VENDOR(*id), USB_ID_PRODUCT(*id),
			 USB_ID_VENDOR(dst), USB_ID_PRODUCT(dst));
		*id = dst;
		return true;
	}

	return false;
}