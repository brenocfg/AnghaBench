#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct dwc3 {scalar_t__ revision; int pullups_connected; int /*<<< orphan*/  regs; scalar_t__ has_hibernation; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCTL ; 
 int DWC3_DCTL_KEEP_CONNECT ; 
 int DWC3_DCTL_RUN_STOP ; 
 int DWC3_DCTL_TRGTULST_MASK ; 
 int DWC3_DCTL_TRGTULST_RX_DET ; 
 int /*<<< orphan*/  DWC3_DSTS ; 
 int DWC3_DSTS_DEVCTRLHLT ; 
 scalar_t__ DWC3_REVISION_187A ; 
 scalar_t__ DWC3_REVISION_194A ; 
 int ETIMEDOUT ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_gadget_run_stop(struct dwc3 *dwc, int is_on, int suspend)
{
	u32			reg;
	u32			timeout = 500;

	if (pm_runtime_suspended(dwc->dev))
		return 0;

	reg = dwc3_readl(dwc->regs, DWC3_DCTL);
	if (is_on) {
		if (dwc->revision <= DWC3_REVISION_187A) {
			reg &= ~DWC3_DCTL_TRGTULST_MASK;
			reg |= DWC3_DCTL_TRGTULST_RX_DET;
		}

		if (dwc->revision >= DWC3_REVISION_194A)
			reg &= ~DWC3_DCTL_KEEP_CONNECT;
		reg |= DWC3_DCTL_RUN_STOP;

		if (dwc->has_hibernation)
			reg |= DWC3_DCTL_KEEP_CONNECT;

		dwc->pullups_connected = true;
	} else {
		reg &= ~DWC3_DCTL_RUN_STOP;

		if (dwc->has_hibernation && !suspend)
			reg &= ~DWC3_DCTL_KEEP_CONNECT;

		dwc->pullups_connected = false;
	}

	dwc3_writel(dwc->regs, DWC3_DCTL, reg);

	do {
		reg = dwc3_readl(dwc->regs, DWC3_DSTS);
		reg &= DWC3_DSTS_DEVCTRLHLT;
	} while (--timeout && !(!is_on ^ !reg));

	if (!timeout)
		return -ETIMEDOUT;

	return 0;
}