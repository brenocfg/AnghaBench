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
struct TYPE_2__ {scalar_t__ host_dma; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; TYPE_1__ params; } ;
struct dwc2_host_chan {int hc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  GINTMSK ; 
 int GINTSTS_HCHINT ; 
 int /*<<< orphan*/  HAINTMSK ; 
 scalar_t__ dbg_hc (struct dwc2_host_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dwc2_hc_enable_dma_ints (struct dwc2_hsotg*,struct dwc2_host_chan*) ; 
 int /*<<< orphan*/  dwc2_hc_enable_slave_ints (struct dwc2_hsotg*,struct dwc2_host_chan*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hc_enable_ints(struct dwc2_hsotg *hsotg,
				struct dwc2_host_chan *chan)
{
	u32 intmsk;

	if (hsotg->params.host_dma) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA enabled\n");
		dwc2_hc_enable_dma_ints(hsotg, chan);
	} else {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA disabled\n");
		dwc2_hc_enable_slave_ints(hsotg, chan);
	}

	/* Enable the top level host channel interrupt */
	intmsk = dwc2_readl(hsotg, HAINTMSK);
	intmsk |= 1 << chan->hc_num;
	dwc2_writel(hsotg, intmsk, HAINTMSK);
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set HAINTMSK to %08x\n", intmsk);

	/* Make sure host channel interrupts are enabled */
	intmsk = dwc2_readl(hsotg, GINTMSK);
	intmsk |= GINTSTS_HCHINT;
	dwc2_writel(hsotg, intmsk, GINTMSK);
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "set GINTMSK to %08x\n", intmsk);
}