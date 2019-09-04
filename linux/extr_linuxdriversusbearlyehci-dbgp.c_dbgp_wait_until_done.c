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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pids; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int DBGP_ERR_BAD ; 
 unsigned int DBGP_GO ; 
 scalar_t__ DBGP_PID_GET (scalar_t__) ; 
 int DBGP_TIMEOUT ; 
 scalar_t__ USB_PID_NAK ; 
 scalar_t__ USB_PID_NYET ; 
 int /*<<< orphan*/  dbgp_breath () ; 
 int dbgp_not_safe ; 
 int dbgp_wait_until_complete () ; 
 TYPE_1__* ehci_debug ; 
 scalar_t__ readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dbgp_wait_until_done(unsigned ctrl, int loop)
{
	u32 pids, lpid;
	int ret;

retry:
	writel(ctrl | DBGP_GO, &ehci_debug->control);
	ret = dbgp_wait_until_complete();
	pids = readl(&ehci_debug->pids);
	lpid = DBGP_PID_GET(pids);

	if (ret < 0) {
		/* A -DBGP_TIMEOUT failure here means the device has
		 * failed, perhaps because it was unplugged, in which
		 * case we do not want to hang the system so the dbgp
		 * will be marked as unsafe to use.  EHCI reset is the
		 * only way to recover if you unplug the dbgp device.
		 */
		if (ret == -DBGP_TIMEOUT && !dbgp_not_safe)
			dbgp_not_safe = 1;
		if (ret == -DBGP_ERR_BAD && --loop > 0)
			goto retry;
		return ret;
	}

	/*
	 * If the port is getting full or it has dropped data
	 * start pacing ourselves, not necessary but it's friendly.
	 */
	if ((lpid == USB_PID_NAK) || (lpid == USB_PID_NYET))
		dbgp_breath();

	/* If I get a NACK reissue the transmission */
	if (lpid == USB_PID_NAK) {
		if (--loop > 0)
			goto retry;
	}

	return ret;
}