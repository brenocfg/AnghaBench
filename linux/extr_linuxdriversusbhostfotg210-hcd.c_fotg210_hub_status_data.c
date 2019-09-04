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
typedef  int u32 ;
struct usb_hcd {int dummy; } ;
struct fotg210_hcd {int resuming_ports; int /*<<< orphan*/  lock; scalar_t__* reset_done; int /*<<< orphan*/  port_c_suspend; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_status; } ;

/* Variables and functions */
 int PORT_CSC ; 
 int PORT_PEC ; 
 int STS_PCD ; 
 int fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fotg210_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);
	u32 temp, status;
	u32 mask;
	int retval = 1;
	unsigned long flags;

	/* init status to no-changes */
	buf[0] = 0;

	/* Inform the core about resumes-in-progress by returning
	 * a non-zero value even if there are no status changes.
	 */
	status = fotg210->resuming_ports;

	mask = PORT_CSC | PORT_PEC;
	/* PORT_RESUME from hardware ~= PORT_STAT_C_SUSPEND */

	/* no hub change reports (bit 0) for now (power, ...) */

	/* port N changes (bit N)? */
	spin_lock_irqsave(&fotg210->lock, flags);

	temp = fotg210_readl(fotg210, &fotg210->regs->port_status);

	/*
	 * Return status information even for ports with OWNER set.
	 * Otherwise hub_wq wouldn't see the disconnect event when a
	 * high-speed device is switched over to the companion
	 * controller by the user.
	 */

	if ((temp & mask) != 0 || test_bit(0, &fotg210->port_c_suspend) ||
			(fotg210->reset_done[0] &&
			time_after_eq(jiffies, fotg210->reset_done[0]))) {
		buf[0] |= 1 << 1;
		status = STS_PCD;
	}
	/* FIXME autosuspend idle root hubs */
	spin_unlock_irqrestore(&fotg210->lock, flags);
	return status ? retval : 0;
}