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
struct mxs_saif {scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  fifo_overrun; int /*<<< orphan*/  fifo_underrun; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int BM_SAIF_STAT_FIFO_OVERFLOW_IRQ ; 
 unsigned int BM_SAIF_STAT_FIFO_UNDERFLOW_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MXS_CLR_ADDR ; 
 scalar_t__ SAIF_CTRL ; 
 scalar_t__ SAIF_STAT ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 

__attribute__((used)) static irqreturn_t mxs_saif_irq(int irq, void *dev_id)
{
	struct mxs_saif *saif = dev_id;
	unsigned int stat;

	stat = __raw_readl(saif->base + SAIF_STAT);
	if (!(stat & (BM_SAIF_STAT_FIFO_UNDERFLOW_IRQ |
			BM_SAIF_STAT_FIFO_OVERFLOW_IRQ)))
		return IRQ_NONE;

	if (stat & BM_SAIF_STAT_FIFO_UNDERFLOW_IRQ) {
		dev_dbg(saif->dev, "underrun!!! %d\n", ++saif->fifo_underrun);
		__raw_writel(BM_SAIF_STAT_FIFO_UNDERFLOW_IRQ,
				saif->base + SAIF_STAT + MXS_CLR_ADDR);
	}

	if (stat & BM_SAIF_STAT_FIFO_OVERFLOW_IRQ) {
		dev_dbg(saif->dev, "overrun!!! %d\n", ++saif->fifo_overrun);
		__raw_writel(BM_SAIF_STAT_FIFO_OVERFLOW_IRQ,
				saif->base + SAIF_STAT + MXS_CLR_ADDR);
	}

	dev_dbg(saif->dev, "SAIF_CTRL %x SAIF_STAT %x\n",
	       __raw_readl(saif->base + SAIF_CTRL),
	       __raw_readl(saif->base + SAIF_STAT));

	return IRQ_HANDLED;
}