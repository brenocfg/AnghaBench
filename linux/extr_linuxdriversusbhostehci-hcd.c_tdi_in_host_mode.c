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
struct ehci_hcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  usbmode; } ;

/* Variables and functions */
 int USBMODE_CM_HC ; 
 int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tdi_in_host_mode (struct ehci_hcd *ehci)
{
	u32		tmp;

	tmp = ehci_readl(ehci, &ehci->regs->usbmode);
	return (tmp & 3) == USBMODE_CM_HC;
}