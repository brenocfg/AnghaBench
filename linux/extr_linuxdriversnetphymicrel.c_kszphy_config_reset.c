#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct phy_device {struct kszphy_priv* priv; } ;
struct kszphy_priv {scalar_t__ led_mode; TYPE_1__* type; int /*<<< orphan*/  rmii_ref_clk_sel_val; scalar_t__ rmii_ref_clk_sel; } ;
struct TYPE_2__ {int /*<<< orphan*/  led_mode_reg; } ;

/* Variables and functions */
 int kszphy_rmii_clk_sel (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kszphy_setup_led (struct phy_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*) ; 

__attribute__((used)) static int kszphy_config_reset(struct phy_device *phydev)
{
	struct kszphy_priv *priv = phydev->priv;
	int ret;

	if (priv->rmii_ref_clk_sel) {
		ret = kszphy_rmii_clk_sel(phydev, priv->rmii_ref_clk_sel_val);
		if (ret) {
			phydev_err(phydev,
				   "failed to set rmii reference clock\n");
			return ret;
		}
	}

	if (priv->led_mode >= 0)
		kszphy_setup_led(phydev, priv->type->led_mode_reg, priv->led_mode);

	return 0;
}