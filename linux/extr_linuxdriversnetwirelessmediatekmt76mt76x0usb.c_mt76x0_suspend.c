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
struct usb_interface {int dummy; } ;
struct mt76x0_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x0_cleanup (struct mt76x0_dev*) ; 
 struct mt76x0_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int mt76x0_suspend(struct usb_interface *usb_intf, pm_message_t state)
{
	struct mt76x0_dev *dev = usb_get_intfdata(usb_intf);

	mt76x0_cleanup(dev);

	return 0;
}