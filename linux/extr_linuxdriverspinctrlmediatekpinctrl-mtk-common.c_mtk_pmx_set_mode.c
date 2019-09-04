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
struct pinctrl_dev {int dummy; } ;
struct mtk_pinctrl {TYPE_1__* devdata; } ;
struct TYPE_2__ {unsigned long port_shf; unsigned long pinmux_offset; int /*<<< orphan*/  (* spec_pinmux_set ) (int /*<<< orphan*/ ,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 long GPIO_MODE_BITS ; 
 unsigned long MAX_GPIO_MODE_PER_REG ; 
 int /*<<< orphan*/  mtk_get_regmap (struct mtk_pinctrl*,unsigned long) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static int mtk_pmx_set_mode(struct pinctrl_dev *pctldev,
		unsigned long pin, unsigned long mode)
{
	unsigned int reg_addr;
	unsigned char bit;
	unsigned int val;
	unsigned int mask = (1L << GPIO_MODE_BITS) - 1;
	struct mtk_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	if (pctl->devdata->spec_pinmux_set)
		pctl->devdata->spec_pinmux_set(mtk_get_regmap(pctl, pin),
					pin, mode);

	reg_addr = ((pin / MAX_GPIO_MODE_PER_REG) << pctl->devdata->port_shf)
			+ pctl->devdata->pinmux_offset;

	mode &= mask;
	bit = pin % MAX_GPIO_MODE_PER_REG;
	mask <<= (GPIO_MODE_BITS * bit);
	val = (mode << (GPIO_MODE_BITS * bit));
	return regmap_update_bits(mtk_get_regmap(pctl, pin),
			reg_addr, mask, val);
}