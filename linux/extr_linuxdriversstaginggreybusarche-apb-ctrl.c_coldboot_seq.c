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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct arche_apb_ctrl_drvdata {scalar_t__ state; int /*<<< orphan*/  resetn_gpio; int /*<<< orphan*/  clk_en_gpio; int /*<<< orphan*/  vio; int /*<<< orphan*/  vcore; int /*<<< orphan*/  spi_en_gpio; scalar_t__ init_disabled; } ;

/* Variables and functions */
 scalar_t__ ARCHE_PLATFORM_STATE_ACTIVE ; 
 scalar_t__ ARCHE_PLATFORM_STATE_FW_FLASHING ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apb_bootret_deassert (struct device*) ; 
 int /*<<< orphan*/  assert_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deassert_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpio_free (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 struct arche_apb_ctrl_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int coldboot_seq(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct arche_apb_ctrl_drvdata *apb = platform_get_drvdata(pdev);
	int ret;

	if (apb->init_disabled ||
	    apb->state == ARCHE_PLATFORM_STATE_ACTIVE)
		return 0;

	/* Hold APB in reset state */
	assert_reset(apb->resetn_gpio);

	if (apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING &&
	    gpio_is_valid(apb->spi_en_gpio))
		devm_gpio_free(dev, apb->spi_en_gpio);

	/* Enable power to APB */
	if (!IS_ERR(apb->vcore)) {
		ret = regulator_enable(apb->vcore);
		if (ret) {
			dev_err(dev, "failed to enable core regulator\n");
			return ret;
		}
	}

	if (!IS_ERR(apb->vio)) {
		ret = regulator_enable(apb->vio);
		if (ret) {
			dev_err(dev, "failed to enable IO regulator\n");
			return ret;
		}
	}

	apb_bootret_deassert(dev);

	/* On DB3 clock was not mandatory */
	if (gpio_is_valid(apb->clk_en_gpio))
		gpio_set_value(apb->clk_en_gpio, 1);

	usleep_range(100, 200);

	/* deassert reset to APB : Active-low signal */
	deassert_reset(apb->resetn_gpio);

	apb->state = ARCHE_PLATFORM_STATE_ACTIVE;

	return 0;
}