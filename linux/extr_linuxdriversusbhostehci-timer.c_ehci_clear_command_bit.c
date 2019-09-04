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
struct ehci_hcd {TYPE_1__* regs; int /*<<< orphan*/  command; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehci_clear_command_bit(struct ehci_hcd *ehci, u32 bit)
{
	ehci->command &= ~bit;
	ehci_writel(ehci, ehci->command, &ehci->regs->command);

	/* unblock posted write */
	ehci_readl(ehci, &ehci->regs->command);
}