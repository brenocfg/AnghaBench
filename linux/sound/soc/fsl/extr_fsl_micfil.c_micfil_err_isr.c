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
 int MICFIL_STAT_BSY_FIL_MASK ; 
 int MICFIL_STAT_FIR_RDY_MASK ; 
 int MICFIL_STAT_LOWFREQF_MASK ; 
 int /*<<< orphan*/  REG_MICFIL_STAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t micfil_err_isr(int irq, void *devid)
{
	struct fsl_micfil *micfil = (struct fsl_micfil *)devid;
	struct platform_device *pdev = micfil->pdev;
	u32 stat_reg;

	regmap_read(micfil->regmap, REG_MICFIL_STAT, &stat_reg);

	if (stat_reg & MICFIL_STAT_BSY_FIL_MASK)
		dev_dbg(&pdev->dev, "isr: Decimation Filter is running\n");

	if (stat_reg & MICFIL_STAT_FIR_RDY_MASK)
		dev_dbg(&pdev->dev, "isr: FIR Filter Data ready\n");

	if (stat_reg & MICFIL_STAT_LOWFREQF_MASK) {
		dev_dbg(&pdev->dev, "isr: ipg_clk_app is too low\n");
		regmap_write_bits(micfil->regmap, REG_MICFIL_STAT,
				  MICFIL_STAT_LOWFREQF_MASK, 1);
	}

	return IRQ_HANDLED;
}