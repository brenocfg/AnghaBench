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
struct wmt_pinctrl_data {int dummy; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMT_FSEL_GPIO_IN ; 
 struct wmt_pinctrl_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  wmt_set_pinmux (struct wmt_pinctrl_data*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void wmt_pmx_gpio_disable_free(struct pinctrl_dev *pctldev,
				      struct pinctrl_gpio_range *range,
				      unsigned offset)
{
	struct wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	/* disable by setting GPIO_IN */
	wmt_set_pinmux(data, WMT_FSEL_GPIO_IN, offset);
}