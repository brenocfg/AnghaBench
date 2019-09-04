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
struct arche_apb_ctrl_drvdata {scalar_t__ state; int /*<<< orphan*/  resetn_gpio; int /*<<< orphan*/  spi_en_gpio; scalar_t__ spi_en_polarity_high; int /*<<< orphan*/  vio; int /*<<< orphan*/  vcore; scalar_t__ init_disabled; } ;

/* Variables and functions */
 scalar_t__ ARCHE_PLATFORM_STATE_FW_FLASHING ; 
 unsigned long GPIOF_OUT_INIT_HIGH ; 
 unsigned long GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  assert_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,unsigned long,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct arche_apb_ctrl_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fw_flashing_seq(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct arche_apb_ctrl_drvdata *apb = platform_get_drvdata(pdev);
	int ret;

	if (apb->init_disabled ||
	    apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING)
		return 0;

	ret = regulator_enable(apb->vcore);
	if (ret) {
		dev_err(dev, "failed to enable core regulator\n");
		return ret;
	}

	ret = regulator_enable(apb->vio);
	if (ret) {
		dev_err(dev, "failed to enable IO regulator\n");
		return ret;
	}

	if (gpio_is_valid(apb->spi_en_gpio)) {
		unsigned long flags;

		if (apb->spi_en_polarity_high)
			flags = GPIOF_OUT_INIT_HIGH;
		else
			flags = GPIOF_OUT_INIT_LOW;

		ret = devm_gpio_request_one(dev, apb->spi_en_gpio,
					    flags, "apb_spi_en");
		if (ret) {
			dev_err(dev, "Failed requesting SPI bus en gpio %d\n",
				apb->spi_en_gpio);
			return ret;
		}
	}

	/* for flashing device should be in reset state */
	assert_reset(apb->resetn_gpio);
	apb->state = ARCHE_PLATFORM_STATE_FW_FLASHING;

	return 0;
}