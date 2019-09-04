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
typedef  size_t u32 ;
struct wmt_pinctrl_data {int /*<<< orphan*/  dev; TYPE_1__* banks; } ;
struct TYPE_2__ {size_t reg_en; size_t reg_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 int EINVAL ; 
 size_t NO_REG ; 
 size_t WMT_BANK_FROM_PIN (unsigned int) ; 
 size_t WMT_BIT_FROM_PIN (unsigned int) ; 
#define  WMT_FSEL_ALT 130 
#define  WMT_FSEL_GPIO_IN 129 
#define  WMT_FSEL_GPIO_OUT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  wmt_clearbits (struct wmt_pinctrl_data*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmt_setbits (struct wmt_pinctrl_data*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wmt_set_pinmux(struct wmt_pinctrl_data *data, unsigned func,
			  unsigned pin)
{
	u32 bank = WMT_BANK_FROM_PIN(pin);
	u32 bit = WMT_BIT_FROM_PIN(pin);
	u32 reg_en = data->banks[bank].reg_en;
	u32 reg_dir = data->banks[bank].reg_dir;

	if (reg_dir == NO_REG) {
		dev_err(data->dev, "pin:%d no direction register defined\n",
			pin);
		return -EINVAL;
	}

	/*
	 * If reg_en == NO_REG, we assume it is a dedicated GPIO and cannot be
	 * disabled (as on VT8500) and that no alternate function is available.
	 */
	switch (func) {
	case WMT_FSEL_GPIO_IN:
		if (reg_en != NO_REG)
			wmt_setbits(data, reg_en, BIT(bit));
		wmt_clearbits(data, reg_dir, BIT(bit));
		break;
	case WMT_FSEL_GPIO_OUT:
		if (reg_en != NO_REG)
			wmt_setbits(data, reg_en, BIT(bit));
		wmt_setbits(data, reg_dir, BIT(bit));
		break;
	case WMT_FSEL_ALT:
		if (reg_en == NO_REG) {
			dev_err(data->dev, "pin:%d no alt function available\n",
				pin);
			return -EINVAL;
		}
		wmt_clearbits(data, reg_en, BIT(bit));
	}

	return 0;
}