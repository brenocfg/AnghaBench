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
struct ehci_hcd_mv {int /*<<< orphan*/  phy_regs; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* phy_deinit ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ehci_clock_disable (struct ehci_hcd_mv*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_ehci_disable(struct ehci_hcd_mv *ehci_mv)
{
	if (ehci_mv->pdata->phy_deinit)
		ehci_mv->pdata->phy_deinit(ehci_mv->phy_regs);
	ehci_clock_disable(ehci_mv);
}