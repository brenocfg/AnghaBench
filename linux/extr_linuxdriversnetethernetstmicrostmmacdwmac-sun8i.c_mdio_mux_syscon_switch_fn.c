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
typedef  int u32 ;
struct sunxi_priv_data {int /*<<< orphan*/  regmap_field; } ;
struct stmmac_priv {int /*<<< orphan*/  device; TYPE_1__* plat; } ;
struct TYPE_2__ {struct sunxi_priv_data* bsp_priv; } ;

/* Variables and functions */
#define  DWMAC_SUN8I_MDIO_MUX_EXTERNAL_ID 129 
#define  DWMAC_SUN8I_MDIO_MUX_INTERNAL_ID 128 
 int EINVAL ; 
 int H3_EPHY_MUX_MASK ; 
 int H3_EPHY_SELECT ; 
 int H3_EPHY_SHUTDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_field_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int sun8i_dwmac_power_internal_phy (struct stmmac_priv*) ; 
 int sun8i_dwmac_reset (struct stmmac_priv*) ; 
 int /*<<< orphan*/  sun8i_dwmac_unpower_internal_phy (struct sunxi_priv_data*) ; 

__attribute__((used)) static int mdio_mux_syscon_switch_fn(int current_child, int desired_child,
				     void *data)
{
	struct stmmac_priv *priv = data;
	struct sunxi_priv_data *gmac = priv->plat->bsp_priv;
	u32 reg, val;
	int ret = 0;
	bool need_power_ephy = false;

	if (current_child ^ desired_child) {
		regmap_field_read(gmac->regmap_field, &reg);
		switch (desired_child) {
		case DWMAC_SUN8I_MDIO_MUX_INTERNAL_ID:
			dev_info(priv->device, "Switch mux to internal PHY");
			val = (reg & ~H3_EPHY_MUX_MASK) | H3_EPHY_SELECT;

			need_power_ephy = true;
			break;
		case DWMAC_SUN8I_MDIO_MUX_EXTERNAL_ID:
			dev_info(priv->device, "Switch mux to external PHY");
			val = (reg & ~H3_EPHY_MUX_MASK) | H3_EPHY_SHUTDOWN;
			need_power_ephy = false;
			break;
		default:
			dev_err(priv->device, "Invalid child ID %x\n",
				desired_child);
			return -EINVAL;
		}
		regmap_field_write(gmac->regmap_field, val);
		if (need_power_ephy) {
			ret = sun8i_dwmac_power_internal_phy(priv);
			if (ret)
				return ret;
		} else {
			sun8i_dwmac_unpower_internal_phy(gmac);
		}
		/* After changing syscon value, the MAC need reset or it will
		 * use the last value (and so the last PHY set).
		 */
		ret = sun8i_dwmac_reset(priv);
	}
	return ret;
}