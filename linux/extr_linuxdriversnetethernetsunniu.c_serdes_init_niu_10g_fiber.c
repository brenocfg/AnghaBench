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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct niu_link_config {scalar_t__ loopback_mode; } ;
struct niu {int /*<<< orphan*/  port; struct niu_link_config link_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESR2_TI_PLL_TEST_CFG_L ; 
 scalar_t__ LOOPBACK_PHY ; 
 int /*<<< orphan*/  NIU_ESR2_DEV_ADDR ; 
 int PLL_RX_CFG_ALIGN_ENA ; 
 int PLL_RX_CFG_ENRX ; 
 int PLL_RX_CFG_ENTEST ; 
 int PLL_RX_CFG_EQ_LP_ADAPTIVE ; 
 int PLL_RX_CFG_LOS_LTHRESH ; 
 int PLL_RX_CFG_TERM_0P8VDDT ; 
 int /*<<< orphan*/  PLL_TEST_CFG_LOOPBACK_CML_DIS ; 
 int PLL_TX_CFG_ENTEST ; 
 int PLL_TX_CFG_ENTX ; 
 int PLL_TX_CFG_SWING_1375MV ; 
 int esr2_set_rx_cfg (struct niu*,unsigned long,int) ; 
 int esr2_set_tx_cfg (struct niu*,unsigned long,int) ; 
 int /*<<< orphan*/  mdio_write (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serdes_init_niu_10g_fiber(struct niu *np)
{
	struct niu_link_config *lp = &np->link_config;
	u32 tx_cfg, rx_cfg;
	unsigned long i;

	tx_cfg = (PLL_TX_CFG_ENTX | PLL_TX_CFG_SWING_1375MV);
	rx_cfg = (PLL_RX_CFG_ENRX | PLL_RX_CFG_TERM_0P8VDDT |
		  PLL_RX_CFG_ALIGN_ENA | PLL_RX_CFG_LOS_LTHRESH |
		  PLL_RX_CFG_EQ_LP_ADAPTIVE);

	if (lp->loopback_mode == LOOPBACK_PHY) {
		u16 test_cfg = PLL_TEST_CFG_LOOPBACK_CML_DIS;

		mdio_write(np, np->port, NIU_ESR2_DEV_ADDR,
			   ESR2_TI_PLL_TEST_CFG_L, test_cfg);

		tx_cfg |= PLL_TX_CFG_ENTEST;
		rx_cfg |= PLL_RX_CFG_ENTEST;
	}

	/* Initialize all 4 lanes of the SERDES.  */
	for (i = 0; i < 4; i++) {
		int err = esr2_set_tx_cfg(np, i, tx_cfg);
		if (err)
			return err;
	}

	for (i = 0; i < 4; i++) {
		int err = esr2_set_rx_cfg(np, i, rx_cfg);
		if (err)
			return err;
	}

	return 0;
}