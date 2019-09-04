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
struct mt7601u_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  mt7601u_cleanup (struct mt7601u_dev*) ; 
 struct mt7601u_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int mt7601u_suspend(struct usb_interface *usb_intf, pm_message_t state)
{
	struct mt7601u_dev *dev = usb_get_intfdata(usb_intf);

	mt7601u_cleanup(dev);

	return 0;
}