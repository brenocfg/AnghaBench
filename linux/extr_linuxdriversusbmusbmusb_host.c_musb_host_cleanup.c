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
struct musb {scalar_t__ port_mode; int /*<<< orphan*/  hcd; } ;

/* Variables and functions */
 scalar_t__ MUSB_PERIPHERAL ; 
 int /*<<< orphan*/  usb_remove_hcd (int /*<<< orphan*/ ) ; 

void musb_host_cleanup(struct musb *musb)
{
	if (musb->port_mode == MUSB_PERIPHERAL)
		return;
	usb_remove_hcd(musb->hcd);
}