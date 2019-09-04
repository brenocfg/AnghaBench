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
struct phy_meson_gxl_usb2_priv {int /*<<< orphan*/  regmap; scalar_t__ is_enabled; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  U2P_R0 ; 
 int /*<<< orphan*/  U2P_R0_POWER_ON_RESET ; 
 struct phy_meson_gxl_usb2_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_meson_gxl_usb2_power_off(struct phy *phy)
{
	struct phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);

	priv->is_enabled = 0;

	/* power off the PHY by putting it into reset mode */
	regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_POWER_ON_RESET,
			   U2P_R0_POWER_ON_RESET);

	return 0;
}