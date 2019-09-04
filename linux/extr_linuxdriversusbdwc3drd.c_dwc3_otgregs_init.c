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
 int /*<<< orphan*/  DWC3_GCTL ; 
 int DWC3_GCTL_GBLHIBERNATIONEN ; 
 int /*<<< orphan*/  DWC3_OCFG ; 
 int DWC3_OCFG_HNPCAP ; 
 int DWC3_OCFG_SFTRSTMASK ; 
 int DWC3_OCFG_SRPCAP ; 
 int /*<<< orphan*/  DWC3_OCTL ; 
 int DWC3_OCTL_DEVSETHNPEN ; 
 int DWC3_OCTL_HNPREQ ; 
 int DWC3_OCTL_HSTSETHNPEN ; 
 int DWC3_OCTL_PERIMODE ; 
 int /*<<< orphan*/  DWC3_OTG_ALL_EVENTS ; 
 int /*<<< orphan*/  dwc3_otg_clear_events (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_otg_disable_events (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_otg_enable_events (struct dwc3*,int /*<<< orphan*/ ) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc3_otgregs_init(struct dwc3 *dwc)
{
	u32 reg;

	/*
	 * Prevent host/device reset from resetting OTG core.
	 * If we don't do this then xhci_reset (USBCMD.HCRST) will reset
	 * the signal outputs sent to the PHY, the OTG FSM logic of the
	 * core and also the resets to the VBUS filters inside the core.
	 */
	reg = dwc3_readl(dwc->regs, DWC3_OCFG);
	reg |= DWC3_OCFG_SFTRSTMASK;
	dwc3_writel(dwc->regs, DWC3_OCFG, reg);

	/* Disable hibernation for simplicity */
	reg = dwc3_readl(dwc->regs, DWC3_GCTL);
	reg &= ~DWC3_GCTL_GBLHIBERNATIONEN;
	dwc3_writel(dwc->regs, DWC3_GCTL, reg);

	/*
	 * Initialize OTG registers as per
	 * Figure 11-4 OTG Driver Overall Programming Flow
	 */
	/* OCFG.SRPCap = 0, OCFG.HNPCap = 0 */
	reg = dwc3_readl(dwc->regs, DWC3_OCFG);
	reg &= ~(DWC3_OCFG_SRPCAP | DWC3_OCFG_HNPCAP);
	dwc3_writel(dwc->regs, DWC3_OCFG, reg);
	/* OEVT = FFFF */
	dwc3_otg_clear_events(dwc);
	/* OEVTEN = 0 */
	dwc3_otg_disable_events(dwc, DWC3_OTG_ALL_EVENTS);
	/* OEVTEN.ConIDStsChngEn = 1. Instead we enable all events */
	dwc3_otg_enable_events(dwc, DWC3_OTG_ALL_EVENTS);
	/*
	 * OCTL.PeriMode = 1, OCTL.DevSetHNPEn = 0, OCTL.HstSetHNPEn = 0,
	 * OCTL.HNPReq = 0
	 */
	reg = dwc3_readl(dwc->regs, DWC3_OCTL);
	reg |= DWC3_OCTL_PERIMODE;
	reg &= ~(DWC3_OCTL_DEVSETHNPEN | DWC3_OCTL_HSTSETHNPEN |
		 DWC3_OCTL_HNPREQ);
	dwc3_writel(dwc->regs, DWC3_OCTL, reg);
}