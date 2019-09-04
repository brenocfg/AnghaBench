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
struct usb_composite_dev {int next_string_id; } ;

/* Variables and functions */
 int ENODEV ; 

int usb_string_id(struct usb_composite_dev *cdev)
{
	if (cdev->next_string_id < 254) {
		/* string id 0 is reserved by USB spec for list of
		 * supported languages */
		/* 255 reserved as well? -- mina86 */
		cdev->next_string_id++;
		return cdev->next_string_id;
	}
	return -ENODEV;
}