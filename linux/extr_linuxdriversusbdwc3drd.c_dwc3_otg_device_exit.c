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
 int DWC3_OCTL_DEVSETHNPEN ; 
 int DWC3_OCTL_HNPREQ ; 
 int DWC3_OCTL_PERIMODE ; 
 int DWC3_OEVTEN_BDEVBHOSTENDEN ; 
 int DWC3_OEVTEN_BDEVHNPCHNGEN ; 
 int DWC3_OEVTEN_BDEVVBUSCHNGEN ; 
 int /*<<< orphan*/  dwc3_otg_disable_events (struct dwc3*,int) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc3_otg_device_exit(struct dwc3 *dwc)
{
	u32 reg;

	/*
	 * Exit from B-device flow as per
	 * Figure 11-4 OTG Driver Overall Programming Flow
	 */

	/*
	 * OEVTEN.OTGBDevHNPChngEvntEn = 0
	 * OEVTEN.OTGBDevVBusChngEvntEn = 0
	 * OEVTEN.OTGBDevBHostEndEvntEn = 0
	 */
	dwc3_otg_disable_events(dwc, DWC3_OEVTEN_BDEVHNPCHNGEN |
				DWC3_OEVTEN_BDEVVBUSCHNGEN |
				DWC3_OEVTEN_BDEVBHOSTENDEN);

	/* OCTL.DevSetHNPEn = 0, OCTL.HNPReq = 0, OCTL.PeriMode=1 */
	reg = dwc3_readl(dwc->regs, DWC3_OCTL);
	reg &= ~(DWC3_OCTL_DEVSETHNPEN | DWC3_OCTL_HNPREQ);
	reg |= DWC3_OCTL_PERIMODE;
	dwc3_writel(dwc->regs, DWC3_OCTL, reg);
}