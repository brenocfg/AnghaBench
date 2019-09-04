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

void dwc2_dump_host_registers(struct dwc2_hsotg *hsotg)
{
#ifdef DEBUG
	u32 __iomem *addr;
	int i;

	dev_dbg(hsotg->dev, "Host Global Registers\n");
	addr = hsotg->regs + HCFG;
	dev_dbg(hsotg->dev, "HCFG	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, HCFG));
	addr = hsotg->regs + HFIR;
	dev_dbg(hsotg->dev, "HFIR	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, HFIR));
	addr = hsotg->regs + HFNUM;
	dev_dbg(hsotg->dev, "HFNUM	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, HFNUM));
	addr = hsotg->regs + HPTXSTS;
	dev_dbg(hsotg->dev, "HPTXSTS	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, HPTXSTS));
	addr = hsotg->regs + HAINT;
	dev_dbg(hsotg->dev, "HAINT	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, HAINT));
	addr = hsotg->regs + HAINTMSK;
	dev_dbg(hsotg->dev, "HAINTMSK	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, HAINTMSK));
	if (hsotg->params.dma_desc_enable) {
		addr = hsotg->regs + HFLBADDR;
		dev_dbg(hsotg->dev, "HFLBADDR @0x%08lX : 0x%08X\n",
			(unsigned long)addr, dwc2_readl(hsotg, HFLBADDR));
	}

	addr = hsotg->regs + HPRT0;
	dev_dbg(hsotg->dev, "HPRT0	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, HPRT0));

	for (i = 0; i < hsotg->params.host_channels; i++) {
		dev_dbg(hsotg->dev, "Host Channel %d Specific Registers\n", i);
		addr = hsotg->regs + HCCHAR(i);
		dev_dbg(hsotg->dev, "HCCHAR	 @0x%08lX : 0x%08X\n",
			(unsigned long)addr, dwc2_readl(hsotg, HCCHAR(i)));
		addr = hsotg->regs + HCSPLT(i);
		dev_dbg(hsotg->dev, "HCSPLT	 @0x%08lX : 0x%08X\n",
			(unsigned long)addr, dwc2_readl(hsotg, HCSPLT(i)));
		addr = hsotg->regs + HCINT(i);
		dev_dbg(hsotg->dev, "HCINT	 @0x%08lX : 0x%08X\n",
			(unsigned long)addr, dwc2_readl(hsotg, HCINT(i)));
		addr = hsotg->regs + HCINTMSK(i);
		dev_dbg(hsotg->dev, "HCINTMSK	 @0x%08lX : 0x%08X\n",
			(unsigned long)addr, dwc2_readl(hsotg, HCINTMSK(i)));
		addr = hsotg->regs + HCTSIZ(i);
		dev_dbg(hsotg->dev, "HCTSIZ	 @0x%08lX : 0x%08X\n",
			(unsigned long)addr, dwc2_readl(hsotg, HCTSIZ(i)));
		addr = hsotg->regs + HCDMA(i);
		dev_dbg(hsotg->dev, "HCDMA	 @0x%08lX : 0x%08X\n",
			(unsigned long)addr, dwc2_readl(hsotg, HCDMA(i)));
		if (hsotg->params.dma_desc_enable) {
			addr = hsotg->regs + HCDMAB(i);
			dev_dbg(hsotg->dev, "HCDMAB	 @0x%08lX : 0x%08X\n",
				(unsigned long)addr, dwc2_readl(hsotg,
								HCDMAB(i)));
		}
	}
#endif
}