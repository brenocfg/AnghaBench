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
typedef  int u32 ;
struct ehci_hcd {int command; TYPE_1__* regs; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; int /*<<< orphan*/  intr_enable; } ;

/* Variables and functions */
 int CMD_IAAD ; 
 int CMD_RUN ; 
 int /*<<< orphan*/  STS_HALT ; 
 int ehci_handshake (struct ehci_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ehci_is_TDI (struct ehci_hcd*) ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdi_in_host_mode (struct ehci_hcd*) ; 

__attribute__((used)) static int ehci_halt (struct ehci_hcd *ehci)
{
	u32	temp;

	spin_lock_irq(&ehci->lock);

	/* disable any irqs left enabled by previous code */
	ehci_writel(ehci, 0, &ehci->regs->intr_enable);

	if (ehci_is_TDI(ehci) && !tdi_in_host_mode(ehci)) {
		spin_unlock_irq(&ehci->lock);
		return 0;
	}

	/*
	 * This routine gets called during probe before ehci->command
	 * has been initialized, so we can't rely on its value.
	 */
	ehci->command &= ~CMD_RUN;
	temp = ehci_readl(ehci, &ehci->regs->command);
	temp &= ~(CMD_RUN | CMD_IAAD);
	ehci_writel(ehci, temp, &ehci->regs->command);

	spin_unlock_irq(&ehci->lock);
	synchronize_irq(ehci_to_hcd(ehci)->irq);

	return ehci_handshake(ehci, &ehci->regs->status,
			  STS_HALT, STS_HALT, 16 * 125);
}