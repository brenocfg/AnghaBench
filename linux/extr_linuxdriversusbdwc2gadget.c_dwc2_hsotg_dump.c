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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void dwc2_hsotg_dump(struct dwc2_hsotg *hsotg)
{
#ifdef DEBUG
	struct device *dev = hsotg->dev;
	u32 val;
	int idx;

	dev_info(dev, "DCFG=0x%08x, DCTL=0x%08x, DIEPMSK=%08x\n",
		 dwc2_readl(hsotg, DCFG), dwc2_readl(hsotg, DCTL),
		 dwc2_readl(hsotg, DIEPMSK));

	dev_info(dev, "GAHBCFG=0x%08x, GHWCFG1=0x%08x\n",
		 dwc2_readl(hsotg, GAHBCFG), dwc2_readl(hsotg, GHWCFG1));

	dev_info(dev, "GRXFSIZ=0x%08x, GNPTXFSIZ=0x%08x\n",
		 dwc2_readl(hsotg, GRXFSIZ), dwc2_readl(hsotg, GNPTXFSIZ));

	/* show periodic fifo settings */

	for (idx = 1; idx < hsotg->num_of_eps; idx++) {
		val = dwc2_readl(hsotg, DPTXFSIZN(idx));
		dev_info(dev, "DPTx[%d] FSize=%d, StAddr=0x%08x\n", idx,
			 val >> FIFOSIZE_DEPTH_SHIFT,
			 val & FIFOSIZE_STARTADDR_MASK);
	}

	for (idx = 0; idx < hsotg->num_of_eps; idx++) {
		dev_info(dev,
			 "ep%d-in: EPCTL=0x%08x, SIZ=0x%08x, DMA=0x%08x\n", idx,
			 dwc2_readl(hsotg, DIEPCTL(idx)),
			 dwc2_readl(hsotg, DIEPTSIZ(idx)),
			 dwc2_readl(hsotg, DIEPDMA(idx)));

		val = dwc2_readl(hsotg, DOEPCTL(idx));
		dev_info(dev,
			 "ep%d-out: EPCTL=0x%08x, SIZ=0x%08x, DMA=0x%08x\n",
			 idx, dwc2_readl(hsotg, DOEPCTL(idx)),
			 dwc2_readl(hsotg, DOEPTSIZ(idx)),
			 dwc2_readl(hsotg, DOEPDMA(idx)));
	}

	dev_info(dev, "DVBUSDIS=0x%08x, DVBUSPULSE=%08x\n",
		 dwc2_readl(hsotg, DVBUSDIS), dwc2_readl(hsotg, DVBUSPULSE));
#endif
}