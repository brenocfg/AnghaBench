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
struct rk_priv_data {int /*<<< orphan*/  grf; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int GRF_BIT (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int RK3228_GMAC_PHY_INTF_SEL_RMII ; 
 int RK3228_GMAC_RMII_MODE ; 
 int /*<<< orphan*/  RK3228_GRF_MAC_CON1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rk3228_set_to_rmii(struct rk_priv_data *bsp_priv)
{
	struct device *dev = &bsp_priv->pdev->dev;

	if (IS_ERR(bsp_priv->grf)) {
		dev_err(dev, "Missing rockchip,grf property\n");
		return;
	}

	regmap_write(bsp_priv->grf, RK3228_GRF_MAC_CON1,
		     RK3228_GMAC_PHY_INTF_SEL_RMII |
		     RK3228_GMAC_RMII_MODE);

	/* set MAC to RMII mode */
	regmap_write(bsp_priv->grf, RK3228_GRF_MAC_CON1, GRF_BIT(11));
}