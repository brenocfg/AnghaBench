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
struct ehci_hcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  usbmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBMODE_BE ; 
 int /*<<< orphan*/  USBMODE_CM_HC ; 
 scalar_t__ ehci_big_endian_mmio (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tdi_reset (struct ehci_hcd *ehci)
{
	u32		tmp;

	tmp = ehci_readl(ehci, &ehci->regs->usbmode);
	tmp |= USBMODE_CM_HC;
	/* The default byte access to MMR space is LE after
	 * controller reset. Set the required endian mode
	 * for transfer buffers to match the host microprocessor
	 */
	if (ehci_big_endian_mmio(ehci))
		tmp |= USBMODE_BE;
	ehci_writel(ehci, tmp, &ehci->regs->usbmode);
}