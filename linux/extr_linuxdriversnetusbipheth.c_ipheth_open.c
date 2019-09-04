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
struct usb_device {int dummy; } ;
struct net_device {int dummy; } ;
struct ipheth_device {int /*<<< orphan*/  carrier_work; struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPHETH_ALT_INTFNUM ; 
 int /*<<< orphan*/  IPHETH_CARRIER_CHECK_TIMEOUT ; 
 int /*<<< orphan*/  IPHETH_INTFNUM ; 
 int ipheth_carrier_set (struct ipheth_device*) ; 
 int ipheth_rx_submit (struct ipheth_device*,int /*<<< orphan*/ ) ; 
 struct ipheth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipheth_open(struct net_device *net)
{
	struct ipheth_device *dev = netdev_priv(net);
	struct usb_device *udev = dev->udev;
	int retval = 0;

	usb_set_interface(udev, IPHETH_INTFNUM, IPHETH_ALT_INTFNUM);

	retval = ipheth_carrier_set(dev);
	if (retval)
		return retval;

	retval = ipheth_rx_submit(dev, GFP_KERNEL);
	if (retval)
		return retval;

	schedule_delayed_work(&dev->carrier_work, IPHETH_CARRIER_CHECK_TIMEOUT);
	return retval;
}