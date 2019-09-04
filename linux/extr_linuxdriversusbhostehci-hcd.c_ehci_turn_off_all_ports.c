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
struct ehci_hcd {TYPE_1__* regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  hcs_params; } ;
struct TYPE_2__ {int /*<<< orphan*/ * port_status; } ;

/* Variables and functions */
 int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_RWC_BITS ; 
 int /*<<< orphan*/  ehci_port_power (struct ehci_hcd*,int,int) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehci_turn_off_all_ports(struct ehci_hcd *ehci)
{
	int	port = HCS_N_PORTS(ehci->hcs_params);

	while (port--) {
		spin_unlock_irq(&ehci->lock);
		ehci_port_power(ehci, port, false);
		spin_lock_irq(&ehci->lock);
		ehci_writel(ehci, PORT_RWC_BITS,
				&ehci->regs->port_status[port]);
	}
}