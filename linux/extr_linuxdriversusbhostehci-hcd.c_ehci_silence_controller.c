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
struct ehci_hcd {int /*<<< orphan*/  lock; TYPE_1__* regs; int /*<<< orphan*/  rh_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  configured_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_RH_HALTED ; 
 int /*<<< orphan*/  ehci_halt (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_turn_off_all_ports (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehci_silence_controller(struct ehci_hcd *ehci)
{
	ehci_halt(ehci);

	spin_lock_irq(&ehci->lock);
	ehci->rh_state = EHCI_RH_HALTED;
	ehci_turn_off_all_ports(ehci);

	/* make BIOS/etc use companion controller during reboot */
	ehci_writel(ehci, 0, &ehci->regs->configured_flag);

	/* unblock posted writes */
	ehci_readl(ehci, &ehci->regs->configured_flag);
	spin_unlock_irq(&ehci->lock);
}