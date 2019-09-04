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
struct rockchip_pinctrl {struct regmap* regmap_base; struct regmap* regmap_pmu; } ;
struct rockchip_pin_bank {int bank_num; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int RV1108_SCHMITT_BANK_STRIDE ; 
 int RV1108_SCHMITT_GRF_OFFSET ; 
 int RV1108_SCHMITT_PINS_PER_GRF_REG ; 
 int RV1108_SCHMITT_PINS_PER_PMU_REG ; 
 int RV1108_SCHMITT_PMU_OFFSET ; 

__attribute__((used)) static int rv1108_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	int pins_per_reg;

	if (bank->bank_num == 0) {
		*regmap = info->regmap_pmu;
		*reg = RV1108_SCHMITT_PMU_OFFSET;
		pins_per_reg = RV1108_SCHMITT_PINS_PER_PMU_REG;
	} else {
		*regmap = info->regmap_base;
		*reg = RV1108_SCHMITT_GRF_OFFSET;
		pins_per_reg = RV1108_SCHMITT_PINS_PER_GRF_REG;
		*reg += (bank->bank_num  - 1) * RV1108_SCHMITT_BANK_STRIDE;
	}
	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;

	return 0;
}