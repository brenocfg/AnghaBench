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

void dwc2_dump_global_registers(struct dwc2_hsotg *hsotg)
{
#ifdef DEBUG
	u32 __iomem *addr;

	dev_dbg(hsotg->dev, "Core Global Registers\n");
	addr = hsotg->regs + GOTGCTL;
	dev_dbg(hsotg->dev, "GOTGCTL	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GOTGCTL));
	addr = hsotg->regs + GOTGINT;
	dev_dbg(hsotg->dev, "GOTGINT	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GOTGINT));
	addr = hsotg->regs + GAHBCFG;
	dev_dbg(hsotg->dev, "GAHBCFG	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GAHBCFG));
	addr = hsotg->regs + GUSBCFG;
	dev_dbg(hsotg->dev, "GUSBCFG	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GUSBCFG));
	addr = hsotg->regs + GRSTCTL;
	dev_dbg(hsotg->dev, "GRSTCTL	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GRSTCTL));
	addr = hsotg->regs + GINTSTS;
	dev_dbg(hsotg->dev, "GINTSTS	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GINTSTS));
	addr = hsotg->regs + GINTMSK;
	dev_dbg(hsotg->dev, "GINTMSK	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GINTMSK));
	addr = hsotg->regs + GRXSTSR;
	dev_dbg(hsotg->dev, "GRXSTSR	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GRXSTSR));
	addr = hsotg->regs + GRXFSIZ;
	dev_dbg(hsotg->dev, "GRXFSIZ	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GRXFSIZ));
	addr = hsotg->regs + GNPTXFSIZ;
	dev_dbg(hsotg->dev, "GNPTXFSIZ	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GNPTXFSIZ));
	addr = hsotg->regs + GNPTXSTS;
	dev_dbg(hsotg->dev, "GNPTXSTS	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GNPTXSTS));
	addr = hsotg->regs + GI2CCTL;
	dev_dbg(hsotg->dev, "GI2CCTL	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GI2CCTL));
	addr = hsotg->regs + GPVNDCTL;
	dev_dbg(hsotg->dev, "GPVNDCTL	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GPVNDCTL));
	addr = hsotg->regs + GGPIO;
	dev_dbg(hsotg->dev, "GGPIO	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GGPIO));
	addr = hsotg->regs + GUID;
	dev_dbg(hsotg->dev, "GUID	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GUID));
	addr = hsotg->regs + GSNPSID;
	dev_dbg(hsotg->dev, "GSNPSID	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GSNPSID));
	addr = hsotg->regs + GHWCFG1;
	dev_dbg(hsotg->dev, "GHWCFG1	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GHWCFG1));
	addr = hsotg->regs + GHWCFG2;
	dev_dbg(hsotg->dev, "GHWCFG2	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GHWCFG2));
	addr = hsotg->regs + GHWCFG3;
	dev_dbg(hsotg->dev, "GHWCFG3	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GHWCFG3));
	addr = hsotg->regs + GHWCFG4;
	dev_dbg(hsotg->dev, "GHWCFG4	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GHWCFG4));
	addr = hsotg->regs + GLPMCFG;
	dev_dbg(hsotg->dev, "GLPMCFG	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GLPMCFG));
	addr = hsotg->regs + GPWRDN;
	dev_dbg(hsotg->dev, "GPWRDN	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GPWRDN));
	addr = hsotg->regs + GDFIFOCFG;
	dev_dbg(hsotg->dev, "GDFIFOCFG	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, GDFIFOCFG));
	addr = hsotg->regs + HPTXFSIZ;
	dev_dbg(hsotg->dev, "HPTXFSIZ	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, HPTXFSIZ));

	addr = hsotg->regs + PCGCTL;
	dev_dbg(hsotg->dev, "PCGCTL	 @0x%08lX : 0x%08X\n",
		(unsigned long)addr, dwc2_readl(hsotg, PCGCTL));
#endif
}