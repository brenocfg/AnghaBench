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
struct arche_apb_ctrl_drvdata {scalar_t__ state; int /*<<< orphan*/  spi_en_gpio; scalar_t__ init_disabled; } ;

/* Variables and functions */
 scalar_t__ ARCHE_PLATFORM_STATE_FW_FLASHING ; 
 scalar_t__ ARCHE_PLATFORM_STATE_OFF ; 
 scalar_t__ ARCHE_PLATFORM_STATE_STANDBY ; 
 int /*<<< orphan*/  devm_gpio_free (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct arche_apb_ctrl_drvdata* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int standby_boot_seq(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct arche_apb_ctrl_drvdata *apb = platform_get_drvdata(pdev);

	if (apb->init_disabled)
		return 0;

	/*
	 * Even if it is in OFF state,
	 * then we do not want to change the state
	 */
	if (apb->state == ARCHE_PLATFORM_STATE_STANDBY ||
	    apb->state == ARCHE_PLATFORM_STATE_OFF)
		return 0;

	if (apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING &&
	    gpio_is_valid(apb->spi_en_gpio))
		devm_gpio_free(dev, apb->spi_en_gpio);

	/*
	 * As per WDM spec, do nothing
	 *
	 * Pasted from WDM spec,
	 *  - A falling edge on POWEROFF_L is detected (a)
	 *  - WDM enters standby mode, but no output signals are changed
	 */

	/* TODO: POWEROFF_L is input to WDM module  */
	apb->state = ARCHE_PLATFORM_STATE_STANDBY;
	return 0;
}