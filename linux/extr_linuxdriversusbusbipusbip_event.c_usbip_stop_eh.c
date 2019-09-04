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
struct usbip_device {unsigned long event; int /*<<< orphan*/  eh_waitq; } ;

/* Variables and functions */
 unsigned long USBIP_EH_BYE ; 
 int /*<<< orphan*/  usbip_dbg_eh (char*,...) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

void usbip_stop_eh(struct usbip_device *ud)
{
	unsigned long pending = ud->event & ~USBIP_EH_BYE;

	if (!(ud->event & USBIP_EH_BYE))
		usbip_dbg_eh("usbip_eh stopping but not removed\n");

	if (pending)
		usbip_dbg_eh("usbip_eh waiting completion %lx\n", pending);

	wait_event_interruptible(ud->eh_waitq, !(ud->event & ~USBIP_EH_BYE));
	usbip_dbg_eh("usbip_eh has stopped\n");
}