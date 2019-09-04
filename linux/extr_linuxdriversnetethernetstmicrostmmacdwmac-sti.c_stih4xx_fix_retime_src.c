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
typedef  scalar_t__ u32 ;
struct sti_dwmac {scalar_t__ tx_retime_src; scalar_t__ ctrl_reg; scalar_t__ interface; int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk; scalar_t__ ext_phyclk; } ;

/* Variables and functions */
 scalar_t__ DWMAC_125MHZ ; 
 scalar_t__ DWMAC_25MHZ ; 
 scalar_t__ DWMAC_2_5MHZ ; 
 scalar_t__ DWMAC_50MHZ ; 
 scalar_t__ IS_PHY_IF_MODE_RGMII (scalar_t__) ; 
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
 scalar_t__ PHY_INTERFACE_MODE_RMII ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  STIH4XX_RETIME_SRC_MASK ; 
 scalar_t__ TX_RETIME_SRC_CLKGEN ; 
 scalar_t__ TX_RETIME_SRC_PHYCLK ; 
 scalar_t__ TX_RETIME_SRC_TXCLK ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stih4xx_tx_retime_val ; 

__attribute__((used)) static void stih4xx_fix_retime_src(void *priv, u32 spd)
{
	struct sti_dwmac *dwmac = priv;
	u32 src = dwmac->tx_retime_src;
	u32 reg = dwmac->ctrl_reg;
	u32 freq = 0;

	if (dwmac->interface == PHY_INTERFACE_MODE_MII) {
		src = TX_RETIME_SRC_TXCLK;
	} else if (dwmac->interface == PHY_INTERFACE_MODE_RMII) {
		if (dwmac->ext_phyclk) {
			src = TX_RETIME_SRC_PHYCLK;
		} else {
			src = TX_RETIME_SRC_CLKGEN;
			freq = DWMAC_50MHZ;
		}
	} else if (IS_PHY_IF_MODE_RGMII(dwmac->interface)) {
		/* On GiGa clk source can be either ext or from clkgen */
		if (spd == SPEED_1000) {
			freq = DWMAC_125MHZ;
		} else {
			/* Switch to clkgen for these speeds */
			src = TX_RETIME_SRC_CLKGEN;
			if (spd == SPEED_100)
				freq = DWMAC_25MHZ;
			else if (spd == SPEED_10)
				freq = DWMAC_2_5MHZ;
		}
	}

	if (src == TX_RETIME_SRC_CLKGEN && freq)
		clk_set_rate(dwmac->clk, freq);

	regmap_update_bits(dwmac->regmap, reg, STIH4XX_RETIME_SRC_MASK,
			   stih4xx_tx_retime_val[src]);
}