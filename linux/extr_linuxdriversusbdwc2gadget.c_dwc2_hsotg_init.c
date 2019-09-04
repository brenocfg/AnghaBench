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
struct dwc2_hsotg {int phyif; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAINTMSK ; 
 int /*<<< orphan*/  DCTL ; 
 int /*<<< orphan*/  DCTL_SFTDISCON ; 
 int /*<<< orphan*/  DIEPMSK ; 
 int DIEPMSK_AHBERRMSK ; 
 int DIEPMSK_EPDISBLDMSK ; 
 int DIEPMSK_TIMEOUTMSK ; 
 int DIEPMSK_XFERCOMPLMSK ; 
 int /*<<< orphan*/  DOEPMSK ; 
 int DOEPMSK_AHBERRMSK ; 
 int DOEPMSK_EPDISBLDMSK ; 
 int DOEPMSK_SETUPMSK ; 
 int DOEPMSK_XFERCOMPLMSK ; 
 int /*<<< orphan*/  GAHBCFG ; 
 int /*<<< orphan*/  GAHBCFG_DMA_EN ; 
 int /*<<< orphan*/  GNPTXFSIZ ; 
 int /*<<< orphan*/  GRXFSIZ ; 
 int /*<<< orphan*/  GUSBCFG ; 
 int GUSBCFG_HNPCAP ; 
 int GUSBCFG_PHYIF16 ; 
 int GUSBCFG_PHYIF8 ; 
 int GUSBCFG_SRPCAP ; 
 int GUSBCFG_TOUTCAL (int) ; 
 int GUSBCFG_TOUTCAL_MASK ; 
 int GUSBCFG_USBTRDTIM_MASK ; 
 int GUSBCFG_USBTRDTIM_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dwc2_hsotg_init_fifo (struct dwc2_hsotg*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_set_bit (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ using_dma (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_hsotg_init(struct dwc2_hsotg *hsotg)
{
	u32 trdtim;
	u32 usbcfg;
	/* unmask subset of endpoint interrupts */

	dwc2_writel(hsotg, DIEPMSK_TIMEOUTMSK | DIEPMSK_AHBERRMSK |
		    DIEPMSK_EPDISBLDMSK | DIEPMSK_XFERCOMPLMSK,
		    DIEPMSK);

	dwc2_writel(hsotg, DOEPMSK_SETUPMSK | DOEPMSK_AHBERRMSK |
		    DOEPMSK_EPDISBLDMSK | DOEPMSK_XFERCOMPLMSK,
		    DOEPMSK);

	dwc2_writel(hsotg, 0, DAINTMSK);

	/* Be in disconnected state until gadget is registered */
	dwc2_set_bit(hsotg, DCTL, DCTL_SFTDISCON);

	/* setup fifos */

	dev_dbg(hsotg->dev, "GRXFSIZ=0x%08x, GNPTXFSIZ=0x%08x\n",
		dwc2_readl(hsotg, GRXFSIZ),
		dwc2_readl(hsotg, GNPTXFSIZ));

	dwc2_hsotg_init_fifo(hsotg);

	/* keep other bits untouched (so e.g. forced modes are not lost) */
	usbcfg = dwc2_readl(hsotg, GUSBCFG);
	usbcfg &= ~(GUSBCFG_TOUTCAL_MASK | GUSBCFG_PHYIF16 | GUSBCFG_SRPCAP |
		GUSBCFG_HNPCAP | GUSBCFG_USBTRDTIM_MASK);

	/* set the PLL on, remove the HNP/SRP and set the PHY */
	trdtim = (hsotg->phyif == GUSBCFG_PHYIF8) ? 9 : 5;
	usbcfg |= hsotg->phyif | GUSBCFG_TOUTCAL(7) |
		(trdtim << GUSBCFG_USBTRDTIM_SHIFT);
	dwc2_writel(hsotg, usbcfg, GUSBCFG);

	if (using_dma(hsotg))
		dwc2_set_bit(hsotg, GAHBCFG, GAHBCFG_DMA_EN);
}