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
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int power_budget; TYPE_1__ self; int /*<<< orphan*/  state; } ;
struct sl811 {TYPE_2__* board; } ;
struct TYPE_4__ {int power; int /*<<< orphan*/  can_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sl811* hcd_to_sl811 (struct usb_hcd*) ; 
 int /*<<< orphan*/  port_power (struct sl811*,int) ; 

__attribute__((used)) static int
sl811h_start(struct usb_hcd *hcd)
{
	struct sl811		*sl811 = hcd_to_sl811(hcd);

	/* chip has been reset, VBUS power is off */
	hcd->state = HC_STATE_RUNNING;

	if (sl811->board) {
		if (!device_can_wakeup(hcd->self.controller))
			device_init_wakeup(hcd->self.controller,
				sl811->board->can_wakeup);
		hcd->power_budget = sl811->board->power * 2;
	}

	/* enable power and interrupts */
	port_power(sl811, 1);

	return 0;
}