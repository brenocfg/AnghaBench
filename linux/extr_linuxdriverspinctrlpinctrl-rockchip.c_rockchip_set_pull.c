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
struct rockchip_pin_ctrl {int type; int /*<<< orphan*/  (* pull_calc_reg ) (struct rockchip_pin_bank*,int,struct regmap**,int*,int*) ;} ;
struct rockchip_pin_bank {int* pull_type; int /*<<< orphan*/  bank_num; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BIT (int) ; 
 int EINVAL ; 
 int PIN_CONFIG_BIAS_DISABLE ; 
#define  PX30 135 
#define  RK2928 134 
 int RK3066B ; 
#define  RK3128 133 
#define  RK3188 132 
 int RK3188_PULL_BITS_PER_PIN ; 
#define  RK3288 131 
#define  RK3368 130 
#define  RK3399 129 
#define  RV1108 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_update_bits (struct regmap*,int,int,int) ; 
 int regmap_write (struct regmap*,int,int) ; 
 int** rockchip_pull_list ; 
 int /*<<< orphan*/  stub1 (struct rockchip_pin_bank*,int,struct regmap**,int*,int*) ; 

__attribute__((used)) static int rockchip_set_pull(struct rockchip_pin_bank *bank,
					int pin_num, int pull)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	struct rockchip_pin_ctrl *ctrl = info->ctrl;
	struct regmap *regmap;
	int reg, ret, i, pull_type;
	u8 bit;
	u32 data, rmask;

	dev_dbg(info->dev, "setting pull of GPIO%d-%d to %d\n",
		 bank->bank_num, pin_num, pull);

	/* rk3066b does support any pulls */
	if (ctrl->type == RK3066B)
		return pull ? -EINVAL : 0;

	ctrl->pull_calc_reg(bank, pin_num, &regmap, &reg, &bit);

	switch (ctrl->type) {
	case RK2928:
	case RK3128:
		data = BIT(bit + 16);
		if (pull == PIN_CONFIG_BIAS_DISABLE)
			data |= BIT(bit);
		ret = regmap_write(regmap, reg, data);
		break;
	case PX30:
	case RV1108:
	case RK3188:
	case RK3288:
	case RK3368:
	case RK3399:
		pull_type = bank->pull_type[pin_num / 8];
		ret = -EINVAL;
		for (i = 0; i < ARRAY_SIZE(rockchip_pull_list[pull_type]);
			i++) {
			if (rockchip_pull_list[pull_type][i] == pull) {
				ret = i;
				break;
			}
		}

		if (ret < 0) {
			dev_err(info->dev, "unsupported pull setting %d\n",
				pull);
			return ret;
		}

		/* enable the write to the equivalent lower bits */
		data = ((1 << RK3188_PULL_BITS_PER_PIN) - 1) << (bit + 16);
		rmask = data | (data >> 16);
		data |= (ret << bit);

		ret = regmap_update_bits(regmap, reg, rmask, data);
		break;
	default:
		dev_err(info->dev, "unsupported pinctrl type\n");
		return -EINVAL;
	}

	return ret;
}