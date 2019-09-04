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
struct mt7601u_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7601U_STATE_INITIALIZED ; 
 int mt7601u_init_hardware (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mt7601u_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int mt7601u_resume(struct usb_interface *usb_intf)
{
	struct mt7601u_dev *dev = usb_get_intfdata(usb_intf);
	int ret;

	ret = mt7601u_init_hardware(dev);
	if (ret)
		return ret;

	set_bit(MT7601U_STATE_INITIALIZED, &dev->state);

	return 0;
}