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
struct dwc3 {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_OCTL ; 
 int DWC3_OCTL_HSTSETHNPEN ; 
 int DWC3_OCTL_PRTPWRCTL ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc3_otg_host_exit(struct dwc3 *dwc)
{
	u32 reg;

	/*
	 * Exit from A-device flow as per
	 * Figure 11-4 OTG Driver Overall Programming Flow
	 */

	/*
	 * OEVTEN.OTGADevBHostEndEvntEn=0, OEVTEN.OTGADevHNPChngEvntEn=0
	 * OEVTEN.OTGADevSessEndDetEvntEn=0,
	 * OEVTEN.OTGADevHostEvntEn = 0
	 * But we don't disable any OTG events
	 */

	/* OCTL.HstSetHNPEn = 0, OCTL.PrtPwrCtl=0 */
	reg = dwc3_readl(dwc->regs, DWC3_OCTL);
	reg &= ~(DWC3_OCTL_HSTSETHNPEN | DWC3_OCTL_PRTPWRCTL);
	dwc3_writel(dwc->regs, DWC3_OCTL, reg);
}