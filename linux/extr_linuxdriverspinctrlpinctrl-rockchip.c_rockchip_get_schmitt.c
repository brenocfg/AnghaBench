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
struct rockchip_pinctrl {struct rockchip_pin_ctrl* ctrl; } ;
struct rockchip_pin_ctrl {int (* schmitt_calc_reg ) (struct rockchip_pin_bank*,int,struct regmap**,int*,int*) ;} ;
struct rockchip_pin_bank {struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int regmap_read (struct regmap*,int,int*) ; 
 int stub1 (struct rockchip_pin_bank*,int,struct regmap**,int*,int*) ; 

__attribute__((used)) static int rockchip_get_schmitt(struct rockchip_pin_bank *bank, int pin_num)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	struct rockchip_pin_ctrl *ctrl = info->ctrl;
	struct regmap *regmap;
	int reg, ret;
	u8 bit;
	u32 data;

	ret = ctrl->schmitt_calc_reg(bank, pin_num, &regmap, &reg, &bit);
	if (ret)
		return ret;

	ret = regmap_read(regmap, reg, &data);
	if (ret)
		return ret;

	data >>= bit;
	return data & 0x1;
}