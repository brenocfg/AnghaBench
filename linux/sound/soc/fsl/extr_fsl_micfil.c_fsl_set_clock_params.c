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
struct fsl_micfil {int /*<<< orphan*/  regmap; int /*<<< orphan*/  mclk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MICFIL_CTRL2_CICOSR_MASK ; 
 int /*<<< orphan*/  MICFIL_CTRL2_CLKDIV_MASK ; 
 int MICFIL_CTRL2_OSR_DEFAULT ; 
 int /*<<< orphan*/  REG_MICFIL_CTRL2 ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 struct fsl_micfil* dev_get_drvdata (struct device*) ; 
 int fsl_micfil_set_mclk_rate (struct fsl_micfil*,unsigned int) ; 
 int get_clk_div (struct fsl_micfil*,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fsl_set_clock_params(struct device *dev, unsigned int rate)
{
	struct fsl_micfil *micfil = dev_get_drvdata(dev);
	int clk_div;
	int ret = 0;

	ret = fsl_micfil_set_mclk_rate(micfil, rate);
	if (ret < 0)
		dev_err(dev, "failed to set mclk[%lu] to rate %u\n",
			clk_get_rate(micfil->mclk), rate);

	/* set CICOSR */
	ret |= regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL2,
				 MICFIL_CTRL2_CICOSR_MASK,
				 MICFIL_CTRL2_OSR_DEFAULT);
	if (ret)
		dev_err(dev, "failed to set CICOSR in reg 0x%X\n",
			REG_MICFIL_CTRL2);

	/* set CLK_DIV */
	clk_div = get_clk_div(micfil, rate);
	if (clk_div < 0)
		ret = -EINVAL;

	ret |= regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL2,
				 MICFIL_CTRL2_CLKDIV_MASK, clk_div);
	if (ret)
		dev_err(dev, "failed to set CLKDIV in reg 0x%X\n",
			REG_MICFIL_CTRL2);

	return ret;
}