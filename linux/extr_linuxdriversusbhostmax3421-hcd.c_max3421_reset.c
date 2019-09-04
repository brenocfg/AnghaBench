#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* root_hub; scalar_t__ sg_tablesize; } ;
struct usb_hcd {TYPE_2__ self; int /*<<< orphan*/  speed; } ;
struct max3421_hcd {int /*<<< orphan*/  spi_thread; int /*<<< orphan*/  todo; } ;
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_USB2 ; 
 int /*<<< orphan*/  RESET_HCD ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
max3421_reset(struct usb_hcd *hcd)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);

	hcd->self.sg_tablesize = 0;
	hcd->speed = HCD_USB2;
	hcd->self.root_hub->speed = USB_SPEED_FULL;
	set_bit(RESET_HCD, &max3421_hcd->todo);
	wake_up_process(max3421_hcd->spi_thread);
	return 0;
}