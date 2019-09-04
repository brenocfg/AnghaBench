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
typedef  int /*<<< orphan*/  u32 ;
struct pinctrl_gpio_range {int /*<<< orphan*/  gc; } ;
struct pinctrl_dev {int dummy; } ;
struct pic32_pinctrl {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int base; } ;
struct pic32_gpio_bank {scalar_t__ reg_base; TYPE_1__ gpio_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANSEL_REG ; 
 int /*<<< orphan*/  BIT (unsigned int) ; 
 scalar_t__ PIC32_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 struct pic32_gpio_bank* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 struct pic32_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pic32_gpio_request_enable(struct pinctrl_dev *pctldev,
				     struct pinctrl_gpio_range *range,
				     unsigned offset)
{
	struct pic32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct pic32_gpio_bank *bank = gpiochip_get_data(range->gc);
	u32 mask = BIT(offset - bank->gpio_chip.base);

	dev_dbg(pctl->dev, "requesting gpio %d in bank %d with mask 0x%x\n",
		offset, bank->gpio_chip.base, mask);

	writel(mask, bank->reg_base + PIC32_CLR(ANSEL_REG));

	return 0;
}