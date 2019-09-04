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
typedef  int /*<<< orphan*/  u32 ;
struct fotg210_hcd {scalar_t__ resuming_ports; scalar_t__ suspended_ports; scalar_t__ port_c_suspend; int /*<<< orphan*/ * debug; TYPE_1__* regs; int /*<<< orphan*/  next_statechange; int /*<<< orphan*/  rh_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESET ; 
 int /*<<< orphan*/  FOTG210_RH_HALTED ; 
 int /*<<< orphan*/  dbg_cmd (struct fotg210_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgp_external_startup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgp_reset_prep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_to_hcd (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_writel (struct fotg210_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int handshake (struct fotg210_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static int fotg210_reset(struct fotg210_hcd *fotg210)
{
	int retval;
	u32 command = fotg210_readl(fotg210, &fotg210->regs->command);

	/* If the EHCI debug controller is active, special care must be
	 * taken before and after a host controller reset
	 */
	if (fotg210->debug && !dbgp_reset_prep(fotg210_to_hcd(fotg210)))
		fotg210->debug = NULL;

	command |= CMD_RESET;
	dbg_cmd(fotg210, "reset", command);
	fotg210_writel(fotg210, command, &fotg210->regs->command);
	fotg210->rh_state = FOTG210_RH_HALTED;
	fotg210->next_statechange = jiffies;
	retval = handshake(fotg210, &fotg210->regs->command,
			CMD_RESET, 0, 250 * 1000);

	if (retval)
		return retval;

	if (fotg210->debug)
		dbgp_external_startup(fotg210_to_hcd(fotg210));

	fotg210->port_c_suspend = fotg210->suspended_ports =
			fotg210->resuming_ports = 0;
	return retval;
}