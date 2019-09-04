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
struct qcom_usb_hsic_phy {int /*<<< orphan*/  phy_clk; int /*<<< orphan*/  cal_clk; int /*<<< orphan*/  cal_sleep_clk; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct qcom_usb_hsic_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int qcom_usb_hsic_phy_power_off(struct phy *phy)
{
	struct qcom_usb_hsic_phy *uphy = phy_get_drvdata(phy);

	clk_disable_unprepare(uphy->cal_sleep_clk);
	clk_disable_unprepare(uphy->cal_clk);
	clk_disable_unprepare(uphy->phy_clk);

	return 0;
}