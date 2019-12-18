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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_micfil {int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MICFIL_DMA_ENABLED (int) ; 
 int MICFIL_FIFO_NUM ; 
 int MICFIL_FIFO_STAT_FIFOX_OVER_MASK (int) ; 
 int MICFIL_FIFO_STAT_FIFOX_UNDER_MASK (int) ; 
 int MICFIL_OUTPUT_CHANNELS ; 
 int MICFIL_STAT_CHXF_MASK (int) ; 
 int /*<<< orphan*/  REG_MICFIL_CTRL1 ; 
 int /*<<< orphan*/  REG_MICFIL_FIFO_STAT ; 
 int /*<<< orphan*/  REG_MICFIL_STAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t micfil_isr(int irq, void *devid)
{
	struct fsl_micfil *micfil = (struct fsl_micfil *)devid;
	struct platform_device *pdev = micfil->pdev;
	u32 stat_reg;
	u32 fifo_stat_reg;
	u32 ctrl1_reg;
	bool dma_enabled;
	int i;

	regmap_read(micfil->regmap, REG_MICFIL_STAT, &stat_reg);
	regmap_read(micfil->regmap, REG_MICFIL_CTRL1, &ctrl1_reg);
	regmap_read(micfil->regmap, REG_MICFIL_FIFO_STAT, &fifo_stat_reg);

	dma_enabled = MICFIL_DMA_ENABLED(ctrl1_reg);

	/* Channel 0-7 Output Data Flags */
	for (i = 0; i < MICFIL_OUTPUT_CHANNELS; i++) {
		if (stat_reg & MICFIL_STAT_CHXF_MASK(i))
			dev_dbg(&pdev->dev,
				"Data available in Data Channel %d\n", i);
		/* if DMA is not enabled, field must be written with 1
		 * to clear
		 */
		if (!dma_enabled)
			regmap_write_bits(micfil->regmap,
					  REG_MICFIL_STAT,
					  MICFIL_STAT_CHXF_MASK(i),
					  1);
	}

	for (i = 0; i < MICFIL_FIFO_NUM; i++) {
		if (fifo_stat_reg & MICFIL_FIFO_STAT_FIFOX_OVER_MASK(i))
			dev_dbg(&pdev->dev,
				"FIFO Overflow Exception flag for channel %d\n",
				i);

		if (fifo_stat_reg & MICFIL_FIFO_STAT_FIFOX_UNDER_MASK(i))
			dev_dbg(&pdev->dev,
				"FIFO Underflow Exception flag for channel %d\n",
				i);
	}

	return IRQ_HANDLED;
}