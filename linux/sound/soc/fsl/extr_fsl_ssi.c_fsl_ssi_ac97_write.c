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
struct snd_ac97 {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ac97_reg_lock; int /*<<< orphan*/  clk; struct regmap* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SSI_SACADD ; 
 int /*<<< orphan*/  REG_SSI_SACDAT ; 
 int /*<<< orphan*/  REG_SSI_SACNT ; 
 int /*<<< orphan*/  SSI_SACNT_RDWR_MASK ; 
 int /*<<< orphan*/  SSI_SACNT_WR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 TYPE_1__* fsl_ac97_data ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void fsl_ssi_ac97_write(struct snd_ac97 *ac97, unsigned short reg,
			       unsigned short val)
{
	struct regmap *regs = fsl_ac97_data->regs;
	unsigned int lreg;
	unsigned int lval;
	int ret;

	if (reg > 0x7f)
		return;

	mutex_lock(&fsl_ac97_data->ac97_reg_lock);

	ret = clk_prepare_enable(fsl_ac97_data->clk);
	if (ret) {
		pr_err("ac97 write clk_prepare_enable failed: %d\n",
			ret);
		goto ret_unlock;
	}

	lreg = reg <<  12;
	regmap_write(regs, REG_SSI_SACADD, lreg);

	lval = val << 4;
	regmap_write(regs, REG_SSI_SACDAT, lval);

	regmap_update_bits(regs, REG_SSI_SACNT,
			   SSI_SACNT_RDWR_MASK, SSI_SACNT_WR);
	udelay(100);

	clk_disable_unprepare(fsl_ac97_data->clk);

ret_unlock:
	mutex_unlock(&fsl_ac97_data->ac97_reg_lock);
}