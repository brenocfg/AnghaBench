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
struct snd_ac97 {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ac97_reg_lock; int /*<<< orphan*/  clk; struct regmap* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SSI_SACADD ; 
 int /*<<< orphan*/  REG_SSI_SACDAT ; 
 int /*<<< orphan*/  REG_SSI_SACNT ; 
 int /*<<< orphan*/  SSI_SACNT_RD ; 
 int /*<<< orphan*/  SSI_SACNT_RDWR_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 TYPE_1__* fsl_ac97_data ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned short fsl_ssi_ac97_read(struct snd_ac97 *ac97,
					unsigned short reg)
{
	struct regmap *regs = fsl_ac97_data->regs;
	unsigned short val = 0;
	u32 reg_val;
	unsigned int lreg;
	int ret;

	mutex_lock(&fsl_ac97_data->ac97_reg_lock);

	ret = clk_prepare_enable(fsl_ac97_data->clk);
	if (ret) {
		pr_err("ac97 read clk_prepare_enable failed: %d\n", ret);
		goto ret_unlock;
	}

	lreg = (reg & 0x7f) <<  12;
	regmap_write(regs, REG_SSI_SACADD, lreg);
	regmap_update_bits(regs, REG_SSI_SACNT,
			   SSI_SACNT_RDWR_MASK, SSI_SACNT_RD);

	udelay(100);

	regmap_read(regs, REG_SSI_SACDAT, &reg_val);
	val = (reg_val >> 4) & 0xffff;

	clk_disable_unprepare(fsl_ac97_data->clk);

ret_unlock:
	mutex_unlock(&fsl_ac97_data->ac97_reg_lock);
	return val;
}