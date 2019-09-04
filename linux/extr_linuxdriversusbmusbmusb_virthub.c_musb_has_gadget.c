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
struct musb {scalar_t__ port_mode; } ;

/* Variables and functions */
 scalar_t__ MUSB_HOST ; 

__attribute__((used)) static int musb_has_gadget(struct musb *musb)
{
	/*
	 * In host-only mode we start a connection right away. In OTG mode
	 * we have to wait until we loaded a gadget. We don't really need a
	 * gadget if we operate as a host but we should not start a session
	 * as a device without a gadget or else we explode.
	 */
#ifdef CONFIG_USB_MUSB_HOST
	return 1;
#else
	return musb->port_mode == MUSB_HOST;
#endif
}