#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x0_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int mt76x0_init_hardware (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mt76x0_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int mt76x0_resume(struct usb_interface *usb_intf)
{
	struct mt76x0_dev *dev = usb_get_intfdata(usb_intf);
	int ret;

	ret = mt76x0_init_hardware(dev);
	if (ret)
		return ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mt76.state);

	return 0;
}