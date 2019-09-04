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
struct phy_meson8b_usb2_priv {int /*<<< orphan*/  clk_usb_general; int /*<<< orphan*/  clk_usb; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct phy_meson8b_usb2_priv* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int phy_meson8b_usb2_power_off(struct phy *phy)
{
	struct phy_meson8b_usb2_priv *priv = phy_get_drvdata(phy);

	clk_disable_unprepare(priv->clk_usb);
	clk_disable_unprepare(priv->clk_usb_general);

	return 0;
}