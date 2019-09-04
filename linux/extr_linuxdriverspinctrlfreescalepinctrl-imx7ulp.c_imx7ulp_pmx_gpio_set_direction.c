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
typedef  int u32 ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct imx_pinctrl {scalar_t__ base; struct imx_pin_reg* pin_regs; } ;
struct imx_pin_reg {int mux_reg; } ;

/* Variables and functions */
 int BM_IBE_ENABLED ; 
 int BM_OBE_ENABLED ; 
 int EINVAL ; 
 struct imx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imx7ulp_pmx_gpio_set_direction(struct pinctrl_dev *pctldev,
					  struct pinctrl_gpio_range *range,
					  unsigned offset, bool input)
{
	struct imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	const struct imx_pin_reg *pin_reg;
	u32 reg;

	pin_reg = &ipctl->pin_regs[offset];
	if (pin_reg->mux_reg == -1)
		return -EINVAL;

	reg = readl(ipctl->base + pin_reg->mux_reg);
	if (input)
		reg = (reg & ~BM_OBE_ENABLED) | BM_IBE_ENABLED;
	else
		reg = (reg & ~BM_IBE_ENABLED) | BM_OBE_ENABLED;
	writel(reg, ipctl->base + pin_reg->mux_reg);

	return 0;
}