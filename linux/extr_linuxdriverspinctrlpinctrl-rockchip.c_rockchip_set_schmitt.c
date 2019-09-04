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
typedef  int u8 ;
typedef  int u32 ;
struct rockchip_pinctrl {int /*<<< orphan*/  dev; struct rockchip_pin_ctrl* ctrl; } ;
struct rockchip_pin_ctrl {int (* schmitt_calc_reg ) (struct rockchip_pin_bank*,int,struct regmap**,int*,int*) ;} ;
struct rockchip_pin_bank {int /*<<< orphan*/  bank_num; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int regmap_update_bits (struct regmap*,int,int,int) ; 
 int stub1 (struct rockchip_pin_bank*,int,struct regmap**,int*,int*) ; 

__attribute__((used)) static int rockchip_set_schmitt(struct rockchip_pin_bank *bank,
				int pin_num, int enable)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	struct rockchip_pin_ctrl *ctrl = info->ctrl;
	struct regmap *regmap;
	int reg, ret;
	u8 bit;
	u32 data, rmask;

	dev_dbg(info->dev, "setting input schmitt of GPIO%d-%d to %d\n",
		bank->bank_num, pin_num, enable);

	ret = ctrl->schmitt_calc_reg(bank, pin_num, &regmap, &reg, &bit);
	if (ret)
		return ret;

	/* enable the write to the equivalent lower bits */
	data = BIT(bit + 16) | (enable << bit);
	rmask = BIT(bit + 16) | BIT(bit);

	return regmap_update_bits(regmap, reg, rmask, data);
}