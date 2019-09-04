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
struct usb4604 {struct device* dev; } ;
struct device {int dummy; } ;
typedef  enum usb4604_mode { ____Placeholder_usb4604_mode } usb4604_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  USB4604_MODE_HUB 129 
#define  USB4604_MODE_STANDBY 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int usb4604_connect (struct usb4604*) ; 
 int /*<<< orphan*/  usb4604_reset (struct usb4604*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb4604_switch_mode(struct usb4604 *hub, enum usb4604_mode mode)
{
	struct device *dev = hub->dev;
	int err = 0;

	switch (mode) {
	case USB4604_MODE_HUB:
		err = usb4604_connect(hub);
		break;

	case USB4604_MODE_STANDBY:
		usb4604_reset(hub, 0);
		dev_dbg(dev, "switched to STANDBY mode\n");
		break;

	default:
		dev_err(dev, "unknown mode is requested\n");
		err = -EINVAL;
		break;
	}

	return err;
}