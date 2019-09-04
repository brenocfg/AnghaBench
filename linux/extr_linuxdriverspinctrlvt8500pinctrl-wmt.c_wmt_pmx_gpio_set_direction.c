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
 int /*<<< orphan*/  WMT_FSEL_GPIO_OUT ; 
 struct wmt_pinctrl_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  wmt_set_pinmux (struct wmt_pinctrl_data*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wmt_pmx_gpio_set_direction(struct pinctrl_dev *pctldev,
				      struct pinctrl_gpio_range *range,
				      unsigned offset,
				      bool input)
{
	struct wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	wmt_set_pinmux(data, (input ? WMT_FSEL_GPIO_IN : WMT_FSEL_GPIO_OUT),
		       offset);

	return 0;
}