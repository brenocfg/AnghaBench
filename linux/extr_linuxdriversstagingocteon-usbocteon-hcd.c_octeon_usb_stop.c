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

/* Variables and functions */
 int /*<<< orphan*/  HC_STATE_HALT ; 

__attribute__((used)) static void octeon_usb_stop(struct usb_hcd *hcd)
{
	hcd->state = HC_STATE_HALT;
}