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
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct u132 {int power; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_STATE_HALT ; 
 struct usb_hcd* u132_to_hcd (struct u132*) ; 

__attribute__((used)) static void u132_power(struct u132 *u132, int is_on)
{
	struct usb_hcd *hcd = u132_to_hcd(u132)
		;	/* hub is inactive unless the port is powered */
	if (is_on) {
		if (u132->power)
			return;
		u132->power = 1;
	} else {
		u132->power = 0;
		hcd->state = HC_STATE_HALT;
	}
}