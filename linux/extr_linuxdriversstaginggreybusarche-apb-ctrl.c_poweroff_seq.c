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
struct arche_apb_ctrl_drvdata {scalar_t__ state; int /*<<< orphan*/  resetn_gpio; int /*<<< orphan*/  vio; int /*<<< orphan*/  vcore; int /*<<< orphan*/  clk_en_gpio; int /*<<< orphan*/  spi_en_gpio; scalar_t__ init_disabled; } ;

/* Variables and functions */
 scalar_t__ ARCHE_PLATFORM_STATE_FW_FLASHING ; 
 scalar_t__ ARCHE_PLATFORM_STATE_OFF ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpio_free (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct arche_apb_ctrl_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ regulator_is_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poweroff_seq(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct arche_apb_ctrl_drvdata *apb = platform_get_drvdata(pdev);

	if (apb->init_disabled || apb->state == ARCHE_PLATFORM_STATE_OFF)
		return;

	if (apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING &&
	    gpio_is_valid(apb->spi_en_gpio))
		devm_gpio_free(dev, apb->spi_en_gpio);

	/* disable the clock */
	if (gpio_is_valid(apb->clk_en_gpio))
		gpio_set_value(apb->clk_en_gpio, 0);

	if (!IS_ERR(apb->vcore) && regulator_is_enabled(apb->vcore) > 0)
		regulator_disable(apb->vcore);

	if (!IS_ERR(apb->vio) && regulator_is_enabled(apb->vio) > 0)
		regulator_disable(apb->vio);

	/* As part of exit, put APB back in reset state */
	assert_reset(apb->resetn_gpio);
	apb->state = ARCHE_PLATFORM_STATE_OFF;

	/* TODO: May have to send an event to SVC about this exit */
}