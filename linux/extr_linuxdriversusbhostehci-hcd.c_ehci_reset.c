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
struct ehci_hcd {scalar_t__ resuming_ports; scalar_t__ suspended_ports; scalar_t__ port_c_suspend; int /*<<< orphan*/ * debug; TYPE_1__* regs; scalar_t__ has_hostpc; int /*<<< orphan*/  next_statechange; int /*<<< orphan*/  rh_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  txfill_tuning; int /*<<< orphan*/  usbmode_ex; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_RESET ; 
 int /*<<< orphan*/  EHCI_RH_HALTED ; 
 int TXFIFO_DEFAULT ; 
 int USBMODE_EX_HC ; 
 int USBMODE_EX_VBPS ; 
 int /*<<< orphan*/  dbg_cmd (struct ehci_hcd*,char*,int) ; 
 int /*<<< orphan*/  dbgp_external_startup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgp_reset_prep (int /*<<< orphan*/ ) ; 
 int ehci_handshake (struct ehci_hcd*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ehci_is_TDI (struct ehci_hcd*) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  tdi_reset (struct ehci_hcd*) ; 

int ehci_reset(struct ehci_hcd *ehci)
{
	int	retval;
	u32	command = ehci_readl(ehci, &ehci->regs->command);

	/* If the EHCI debug controller is active, special care must be
	 * taken before and after a host controller reset */
	if (ehci->debug && !dbgp_reset_prep(ehci_to_hcd(ehci)))
		ehci->debug = NULL;

	command |= CMD_RESET;
	dbg_cmd (ehci, "reset", command);
	ehci_writel(ehci, command, &ehci->regs->command);
	ehci->rh_state = EHCI_RH_HALTED;
	ehci->next_statechange = jiffies;
	retval = ehci_handshake(ehci, &ehci->regs->command,
			    CMD_RESET, 0, 250 * 1000);

	if (ehci->has_hostpc) {
		ehci_writel(ehci, USBMODE_EX_HC | USBMODE_EX_VBPS,
				&ehci->regs->usbmode_ex);
		ehci_writel(ehci, TXFIFO_DEFAULT, &ehci->regs->txfill_tuning);
	}
	if (retval)
		return retval;

	if (ehci_is_TDI(ehci))
		tdi_reset (ehci);

	if (ehci->debug)
		dbgp_external_startup(ehci_to_hcd(ehci));

	ehci->port_c_suspend = ehci->suspended_ports =
			ehci->resuming_ports = 0;
	return retval;
}