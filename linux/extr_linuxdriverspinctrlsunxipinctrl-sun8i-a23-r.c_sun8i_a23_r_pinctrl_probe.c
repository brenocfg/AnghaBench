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
struct reset_control {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct reset_control* devm_reset_control_get_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  sun8i_a23_r_pinctrl_data ; 
 int sunxi_pinctrl_init (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun8i_a23_r_pinctrl_probe(struct platform_device *pdev)
{
	struct reset_control *rstc;
	int ret;

	rstc = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (IS_ERR(rstc)) {
		dev_err(&pdev->dev, "Reset controller missing\n");
		return PTR_ERR(rstc);
	}

	ret = reset_control_deassert(rstc);
	if (ret)
		return ret;

	ret = sunxi_pinctrl_init(pdev,
				 &sun8i_a23_r_pinctrl_data);

	if (ret)
		reset_control_assert(rstc);

	return ret;
}