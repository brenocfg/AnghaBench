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
struct ulpi {int dummy; } ;
struct qcom_usb_hsic_phy {int /*<<< orphan*/  phy_clk; int /*<<< orphan*/  cal_clk; int /*<<< orphan*/  cal_sleep_clk; int /*<<< orphan*/  pctl; struct ulpi* ulpi; } ;
struct pinctrl_state {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
 int /*<<< orphan*/  PINCTRL_STATE_DEFAULT ; 
 int PTR_ERR (struct pinctrl_state*) ; 
 int /*<<< orphan*/  ULPI_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULPI_HSIC_CFG ; 
 int /*<<< orphan*/  ULPI_HSIC_IO_CAL ; 
 int /*<<< orphan*/  ULPI_IFC_CTRL ; 
 int ULPI_IFC_CTRL_AUTORESUME ; 
 int /*<<< orphan*/  ULPI_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct qcom_usb_hsic_phy* phy_get_drvdata (struct phy*) ; 
 struct pinctrl_state* pinctrl_lookup_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pinctrl_select_state (int /*<<< orphan*/ ,struct pinctrl_state*) ; 
 int ulpi_write (struct ulpi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qcom_usb_hsic_phy_power_on(struct phy *phy)
{
	struct qcom_usb_hsic_phy *uphy = phy_get_drvdata(phy);
	struct ulpi *ulpi = uphy->ulpi;
	struct pinctrl_state *pins_default;
	int ret;

	ret = clk_prepare_enable(uphy->phy_clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(uphy->cal_clk);
	if (ret)
		goto err_cal;

	ret = clk_prepare_enable(uphy->cal_sleep_clk);
	if (ret)
		goto err_sleep;

	/* Set periodic calibration interval to ~2.048sec in HSIC_IO_CAL_REG */
	ret = ulpi_write(ulpi, ULPI_HSIC_IO_CAL, 0xff);
	if (ret)
		goto err_ulpi;

	/* Enable periodic IO calibration in HSIC_CFG register */
	ret = ulpi_write(ulpi, ULPI_HSIC_CFG, 0xa8);
	if (ret)
		goto err_ulpi;

	/* Configure pins for HSIC functionality */
	pins_default = pinctrl_lookup_state(uphy->pctl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(pins_default))
		return PTR_ERR(pins_default);

	ret = pinctrl_select_state(uphy->pctl, pins_default);
	if (ret)
		goto err_ulpi;

	 /* Enable HSIC mode in HSIC_CFG register */
	ret = ulpi_write(ulpi, ULPI_SET(ULPI_HSIC_CFG), 0x01);
	if (ret)
		goto err_ulpi;

	/* Disable auto-resume */
	ret = ulpi_write(ulpi, ULPI_CLR(ULPI_IFC_CTRL),
			 ULPI_IFC_CTRL_AUTORESUME);
	if (ret)
		goto err_ulpi;

	return ret;
err_ulpi:
	clk_disable_unprepare(uphy->cal_sleep_clk);
err_sleep:
	clk_disable_unprepare(uphy->cal_clk);
err_cal:
	clk_disable_unprepare(uphy->phy_clk);
	return ret;
}