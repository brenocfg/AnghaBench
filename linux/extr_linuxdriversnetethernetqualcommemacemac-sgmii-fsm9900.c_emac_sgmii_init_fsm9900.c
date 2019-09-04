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
struct emac_sgmii {scalar_t__ base; } ;
struct emac_adapter {int /*<<< orphan*/  netdev; struct emac_sgmii phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ EMAC_QSERDES_COM_RESET_SM ; 
 scalar_t__ EMAC_SGMII_PHY_INTERRUPT_MASK ; 
 scalar_t__ EMAC_SGMII_PHY_SERDES_START ; 
 int READY ; 
 int /*<<< orphan*/  SERDES_START ; 
 unsigned int SERDES_START_WAIT_TIMES ; 
 int /*<<< orphan*/  cdr_setting ; 
 int /*<<< orphan*/  emac_reg_write_all (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  physical_coding_sublayer_programming ; 
 int /*<<< orphan*/  pll_setting ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sysclk_refclk_setting ; 
 int /*<<< orphan*/  tx_rx_setting ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int emac_sgmii_init_fsm9900(struct emac_adapter *adpt)
{
	struct emac_sgmii *phy = &adpt->phy;
	unsigned int i;

	emac_reg_write_all(phy->base, physical_coding_sublayer_programming,
			   ARRAY_SIZE(physical_coding_sublayer_programming));
	emac_reg_write_all(phy->base, sysclk_refclk_setting,
			   ARRAY_SIZE(sysclk_refclk_setting));
	emac_reg_write_all(phy->base, pll_setting, ARRAY_SIZE(pll_setting));
	emac_reg_write_all(phy->base, cdr_setting, ARRAY_SIZE(cdr_setting));
	emac_reg_write_all(phy->base, tx_rx_setting, ARRAY_SIZE(tx_rx_setting));

	/* Power up the Ser/Des engine */
	writel(SERDES_START, phy->base + EMAC_SGMII_PHY_SERDES_START);

	for (i = 0; i < SERDES_START_WAIT_TIMES; i++) {
		if (readl(phy->base + EMAC_QSERDES_COM_RESET_SM) & READY)
			break;
		usleep_range(100, 200);
	}

	if (i == SERDES_START_WAIT_TIMES) {
		netdev_err(adpt->netdev, "error: ser/des failed to start\n");
		return -EIO;
	}
	/* Mask out all the SGMII Interrupt */
	writel(0, phy->base + EMAC_SGMII_PHY_INTERRUPT_MASK);

	return 0;
}