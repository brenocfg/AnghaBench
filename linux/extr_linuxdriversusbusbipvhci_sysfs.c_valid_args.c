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
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
#define  USB_SPEED_FULL 132 
#define  USB_SPEED_HIGH 131 
#define  USB_SPEED_LOW 130 
#define  USB_SPEED_SUPER 129 
#define  USB_SPEED_WIRELESS 128 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_speed_string (int) ; 
 int /*<<< orphan*/  valid_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int valid_args(__u32 *pdev_nr, __u32 *rhport,
		      enum usb_device_speed speed)
{
	if (!valid_port(pdev_nr, rhport)) {
		return 0;
	}

	switch (speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
	case USB_SPEED_HIGH:
	case USB_SPEED_WIRELESS:
	case USB_SPEED_SUPER:
		break;
	default:
		pr_err("Failed attach request for unsupported USB speed: %s\n",
			usb_speed_string(speed));
		return 0;
	}

	return 1;
}