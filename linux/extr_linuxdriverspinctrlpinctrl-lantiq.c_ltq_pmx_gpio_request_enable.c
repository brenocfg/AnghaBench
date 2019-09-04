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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct ltq_pinmux_info {int (* apply_mux ) (struct pinctrl_dev*,int,int) ;int /*<<< orphan*/  dev; int /*<<< orphan*/ * mfp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int match_mfp (struct ltq_pinmux_info*,unsigned int) ; 
 int match_mux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ltq_pinmux_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int stub1 (struct pinctrl_dev*,int,int) ; 

__attribute__((used)) static int ltq_pmx_gpio_request_enable(struct pinctrl_dev *pctrldev,
				struct pinctrl_gpio_range *range,
				unsigned pin)
{
	struct ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	int mfp = match_mfp(info, pin);
	int pin_func;

	if (mfp < 0) {
		dev_err(info->dev, "could not find mfp for pin %d\n", pin);
		return -EINVAL;
	}

	pin_func = match_mux(&info->mfp[mfp], 0);
	if (pin_func < 0) {
		dev_err(info->dev, "No GPIO function on pin%d\n", mfp);
		return -EINVAL;
	}

	return info->apply_mux(pctrldev, mfp, pin_func);
}