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
typedef  int uint32_t ;
struct ipq806x_gmac {int phy_mode; int /*<<< orphan*/  nss_common; int /*<<< orphan*/  id; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NSS_COMMON_CLK_DIV0 ; 
 int NSS_COMMON_CLK_DIV_MASK ; 
 int NSS_COMMON_CLK_DIV_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSS_COMMON_CLK_GATE ; 
 int NSS_COMMON_CLK_GATE_GMII_RX_EN (int /*<<< orphan*/ ) ; 
 int NSS_COMMON_CLK_GATE_GMII_TX_EN (int /*<<< orphan*/ ) ; 
 int NSS_COMMON_CLK_GATE_RGMII_RX_EN (int /*<<< orphan*/ ) ; 
 int NSS_COMMON_CLK_GATE_RGMII_TX_EN (int /*<<< orphan*/ ) ; 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int get_clk_div_rgmii (struct ipq806x_gmac*,unsigned int) ; 
 int get_clk_div_sgmii (struct ipq806x_gmac*,unsigned int) ; 
 int /*<<< orphan*/  phy_modes (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipq806x_gmac_set_speed(struct ipq806x_gmac *gmac, unsigned int speed)
{
	uint32_t clk_bits, val;
	int div;

	switch (gmac->phy_mode) {
	case PHY_INTERFACE_MODE_RGMII:
		div = get_clk_div_rgmii(gmac, speed);
		clk_bits = NSS_COMMON_CLK_GATE_RGMII_RX_EN(gmac->id) |
			   NSS_COMMON_CLK_GATE_RGMII_TX_EN(gmac->id);
		break;

	case PHY_INTERFACE_MODE_SGMII:
		div = get_clk_div_sgmii(gmac, speed);
		clk_bits = NSS_COMMON_CLK_GATE_GMII_RX_EN(gmac->id) |
			   NSS_COMMON_CLK_GATE_GMII_TX_EN(gmac->id);
		break;

	default:
		dev_err(&gmac->pdev->dev, "Unsupported PHY mode: \"%s\"\n",
			phy_modes(gmac->phy_mode));
		return -EINVAL;
	}

	/* Disable the clocks */
	regmap_read(gmac->nss_common, NSS_COMMON_CLK_GATE, &val);
	val &= ~clk_bits;
	regmap_write(gmac->nss_common, NSS_COMMON_CLK_GATE, val);

	/* Set the divider */
	regmap_read(gmac->nss_common, NSS_COMMON_CLK_DIV0, &val);
	val &= ~(NSS_COMMON_CLK_DIV_MASK
		 << NSS_COMMON_CLK_DIV_OFFSET(gmac->id));
	val |= div << NSS_COMMON_CLK_DIV_OFFSET(gmac->id);
	regmap_write(gmac->nss_common, NSS_COMMON_CLK_DIV0, val);

	/* Enable the clock back */
	regmap_read(gmac->nss_common, NSS_COMMON_CLK_GATE, &val);
	val |= clk_bits;
	regmap_write(gmac->nss_common, NSS_COMMON_CLK_GATE, val);

	return 0;
}