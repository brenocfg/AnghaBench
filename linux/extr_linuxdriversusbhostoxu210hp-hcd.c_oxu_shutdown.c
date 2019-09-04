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
struct usb_hcd {int dummy; } ;
struct oxu_hcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  configured_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehci_halt (struct oxu_hcd*) ; 
 int /*<<< orphan*/  ehci_turn_off_all_ports (struct oxu_hcd*) ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void oxu_shutdown(struct usb_hcd *hcd)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);

	(void) ehci_halt(oxu);
	ehci_turn_off_all_ports(oxu);

	/* make BIOS/etc use companion controller during reboot */
	writel(0, &oxu->regs->configured_flag);

	/* unblock posted writes */
	readl(&oxu->regs->configured_flag);
}