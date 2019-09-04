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
struct atmel_i2s_dev {int /*<<< orphan*/  regmap; TYPE_1__* gck_param; int /*<<< orphan*/  gclk; } ;
struct TYPE_2__ {int mck; int imckdiv; int /*<<< orphan*/  imckfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_I2SC_CR ; 
 int /*<<< orphan*/  ATMEL_I2SC_CR_CKDIS ; 
 int /*<<< orphan*/  ATMEL_I2SC_CR_CKEN ; 
 int /*<<< orphan*/  ATMEL_I2SC_MR ; 
 unsigned int ATMEL_I2SC_MR_IMCKDIV (int) ; 
 unsigned int ATMEL_I2SC_MR_IMCKDIV_MASK ; 
 unsigned int ATMEL_I2SC_MR_IMCKFS (int /*<<< orphan*/ ) ; 
 unsigned int ATMEL_I2SC_MR_IMCKFS_MASK ; 
 unsigned int ATMEL_I2SC_MR_IMCKMODE_I2SMCK ; 
 unsigned int ATMEL_I2SC_MR_IMCKMODE_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_i2s_switch_mck_generator(struct atmel_i2s_dev *dev,
					  bool enabled)
{
	unsigned int mr, mr_mask;
	unsigned long gclk_rate;
	int ret;

	mr = 0;
	mr_mask = (ATMEL_I2SC_MR_IMCKDIV_MASK |
		   ATMEL_I2SC_MR_IMCKFS_MASK |
		   ATMEL_I2SC_MR_IMCKMODE_MASK);

	if (!enabled) {
		/* Disable the I2S Master Clock generator. */
		ret = regmap_write(dev->regmap, ATMEL_I2SC_CR,
				   ATMEL_I2SC_CR_CKDIS);
		if (ret)
			return ret;

		/* Reset the I2S Master Clock generator settings. */
		ret = regmap_update_bits(dev->regmap, ATMEL_I2SC_MR,
					 mr_mask, mr);
		if (ret)
			return ret;

		/* Disable/unprepare the PMC generated clock. */
		clk_disable_unprepare(dev->gclk);

		return 0;
	}

	if (!dev->gck_param)
		return -EINVAL;

	gclk_rate = dev->gck_param->mck * (dev->gck_param->imckdiv + 1);

	ret = clk_set_rate(dev->gclk, gclk_rate);
	if (ret)
		return ret;

	ret = clk_prepare_enable(dev->gclk);
	if (ret)
		return ret;

	/* Update the Mode Register to generate the I2S Master Clock. */
	mr |= ATMEL_I2SC_MR_IMCKDIV(dev->gck_param->imckdiv);
	mr |= ATMEL_I2SC_MR_IMCKFS(dev->gck_param->imckfs);
	mr |= ATMEL_I2SC_MR_IMCKMODE_I2SMCK;
	ret = regmap_update_bits(dev->regmap, ATMEL_I2SC_MR, mr_mask, mr);
	if (ret)
		return ret;

	/* Finally enable the I2S Master Clock generator. */
	return regmap_write(dev->regmap, ATMEL_I2SC_CR,
			    ATMEL_I2SC_CR_CKEN);
}