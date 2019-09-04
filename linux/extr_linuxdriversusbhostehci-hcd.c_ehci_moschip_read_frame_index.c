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
struct ehci_hcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_index; } ;

/* Variables and functions */
 unsigned int ehci_readl (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned ehci_moschip_read_frame_index(struct ehci_hcd *ehci)
{
	unsigned uf;

	uf = ehci_readl(ehci, &ehci->regs->frame_index);
	if (unlikely((uf & 7) == 0))
		uf = ehci_readl(ehci, &ehci->regs->frame_index);
	return uf;
}