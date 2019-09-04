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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3 {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GCTL_PRTCAP_OTG ; 
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG_SUSPHY ; 
 int /*<<< orphan*/  dwc3_otgregs_init (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_set_prtcap (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dwc3_otg_init(struct dwc3 *dwc)
{
	u32 reg;

	/*
	 * As per Figure 11-4 OTG Driver Overall Programming Flow,
	 * block "Initialize GCTL for OTG operation".
	 */
	/* GCTL.PrtCapDir=2'b11 */
	dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_OTG);
	/* GUSB2PHYCFG0.SusPHY=0 */
	reg = dwc3_readl(dwc->regs, DWC3_GUSB2PHYCFG(0));
	reg &= ~DWC3_GUSB2PHYCFG_SUSPHY;
	dwc3_writel(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);

	/* Initialize OTG registers */
	dwc3_otgregs_init(dwc);
}