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
struct mctrl_gpios {int /*<<< orphan*/ * gpio; } ;
struct device {int dummy; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ dir_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mctrl_gpios* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct mctrl_gpios* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_IN ; 
 int GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int UART_GPIO_MAX ; 
 int /*<<< orphan*/  devm_gpiod_get_index_optional (struct device*,int /*<<< orphan*/ ,unsigned int,int) ; 
 struct mctrl_gpios* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mctrl_gpios_desc ; 

struct mctrl_gpios *mctrl_gpio_init_noauto(struct device *dev, unsigned int idx)
{
	struct mctrl_gpios *gpios;
	enum mctrl_gpio_idx i;

	gpios = devm_kzalloc(dev, sizeof(*gpios), GFP_KERNEL);
	if (!gpios)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < UART_GPIO_MAX; i++) {
		enum gpiod_flags flags;

		if (mctrl_gpios_desc[i].dir_out)
			flags = GPIOD_OUT_LOW;
		else
			flags = GPIOD_IN;

		gpios->gpio[i] =
			devm_gpiod_get_index_optional(dev,
						      mctrl_gpios_desc[i].name,
						      idx, flags);

		if (IS_ERR(gpios->gpio[i]))
			return ERR_CAST(gpios->gpio[i]);
	}

	return gpios;
}