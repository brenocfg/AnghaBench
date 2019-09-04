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
struct mtk_pinctrl {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct mtk_pin_reg_calc {scalar_t__ range; } ;
struct mtk_pin_field {int dummy; } ;
struct TYPE_2__ {struct mtk_pin_reg_calc* reg_cal; } ;

/* Variables and functions */
 int EINVAL ; 
 int PINCTRL_PIN_REG_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mtk_hw_pin_field_lookup (struct mtk_pinctrl*,int,struct mtk_pin_reg_calc const*,struct mtk_pin_field*) ; 

__attribute__((used)) static int mtk_hw_pin_field_get(struct mtk_pinctrl *hw, int pin,
				int field, struct mtk_pin_field *pfd)
{
	const struct mtk_pin_reg_calc *rc;

	if (field < 0 || field >= PINCTRL_PIN_REG_MAX) {
		dev_err(hw->dev, "Invalid Field %d\n", field);
		return -EINVAL;
	}

	if (hw->soc->reg_cal && hw->soc->reg_cal[field].range) {
		rc = &hw->soc->reg_cal[field];
	} else {
		dev_err(hw->dev, "Undefined range for field %d\n", field);
		return -EINVAL;
	}

	return mtk_hw_pin_field_lookup(hw, pin, rc, pfd);
}