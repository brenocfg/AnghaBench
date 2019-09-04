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
struct ulpi_seq {int /*<<< orphan*/  val; scalar_t__ addr; } ;
struct ulpi {int /*<<< orphan*/  dev; } ;
struct qcom_usb_hs_phy {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  sleep_clk; int /*<<< orphan*/  v1p8; int /*<<< orphan*/  v3p3; int /*<<< orphan*/  vbus_notify; scalar_t__ vbus_edev; scalar_t__ reset; struct ulpi_seq* init_seq; struct ulpi* ulpi; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB ; 
 scalar_t__ ULPI_EXT_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int devm_extcon_register_notifier (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int extcon_get_state (scalar_t__,int /*<<< orphan*/ ) ; 
 struct qcom_usb_hs_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  qcom_usb_hs_phy_vbus_notifier (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_set_load (int /*<<< orphan*/ ,int) ; 
 int regulator_set_voltage_triplet (int /*<<< orphan*/ ,int,int,int) ; 
 int reset_control_reset (scalar_t__) ; 
 int ulpi_write (struct ulpi*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_usb_hs_phy_power_on(struct phy *phy)
{
	struct qcom_usb_hs_phy *uphy = phy_get_drvdata(phy);
	struct ulpi *ulpi = uphy->ulpi;
	const struct ulpi_seq *seq;
	int ret, state;

	ret = clk_prepare_enable(uphy->ref_clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(uphy->sleep_clk);
	if (ret)
		goto err_sleep;

	ret = regulator_set_load(uphy->v1p8, 50000);
	if (ret < 0)
		goto err_1p8;

	ret = regulator_enable(uphy->v1p8);
	if (ret)
		goto err_1p8;

	ret = regulator_set_voltage_triplet(uphy->v3p3, 3050000, 3300000,
					    3300000);
	if (ret)
		goto err_3p3;

	ret = regulator_set_load(uphy->v3p3, 50000);
	if (ret < 0)
		goto err_3p3;

	ret = regulator_enable(uphy->v3p3);
	if (ret)
		goto err_3p3;

	for (seq = uphy->init_seq; seq->addr; seq++) {
		ret = ulpi_write(ulpi, ULPI_EXT_VENDOR_SPECIFIC + seq->addr,
				 seq->val);
		if (ret)
			goto err_ulpi;
	}

	if (uphy->reset) {
		ret = reset_control_reset(uphy->reset);
		if (ret)
			goto err_ulpi;
	}

	if (uphy->vbus_edev) {
		state = extcon_get_state(uphy->vbus_edev, EXTCON_USB);
		/* setup initial state */
		qcom_usb_hs_phy_vbus_notifier(&uphy->vbus_notify, state,
					      uphy->vbus_edev);
		ret = devm_extcon_register_notifier(&ulpi->dev, uphy->vbus_edev,
				EXTCON_USB, &uphy->vbus_notify);
		if (ret)
			goto err_ulpi;
	}

	return 0;
err_ulpi:
	regulator_disable(uphy->v3p3);
err_3p3:
	regulator_disable(uphy->v1p8);
err_1p8:
	clk_disable_unprepare(uphy->sleep_clk);
err_sleep:
	clk_disable_unprepare(uphy->ref_clk);
	return ret;
}