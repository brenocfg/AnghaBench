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
struct phy_device {scalar_t__ pause; scalar_t__ asym_pause; scalar_t__ speed; scalar_t__ duplex; } ;
struct emac_adapter {scalar_t__ rx_flow_control; int tx_flow_control; int preamble; int irq_mod; scalar_t__ base; scalar_t__ csr; scalar_t__ single_pause_mode; scalar_t__ automatic; struct phy_device* phydev; } ;

/* Variables and functions */
 int BROAD_EN ; 
 int CRCE ; 
 int DEBUG_MODE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ EMAC_ATHR_HEADER_CTRL ; 
 scalar_t__ EMAC_DMA_MAS_CTRL ; 
 scalar_t__ EMAC_EMAC_WRAPPER_CSR1 ; 
 scalar_t__ EMAC_IRQ_MOD_TIM_INIT ; 
 scalar_t__ EMAC_MAC_CTRL ; 
 scalar_t__ EMAC_RXQ_CTRL_0 ; 
 scalar_t__ EMAC_TXQ_CTRL_0 ; 
 int FLCHK ; 
 int FREQ_MODE ; 
 int FULLD ; 
 int HEADER_CNT_EN ; 
 int HEADER_ENABLE ; 
 int HUGE ; 
 int HUGEN ; 
 int INT_RD_CLR_EN ; 
 int IRQ_MODERATOR2_EN ; 
 int IRQ_MODERATOR_EN ; 
 int LPW_MODE ; 
 int MULTI_ALL ; 
 int PCRCE ; 
 int PRLEN_BMSK ; 
 int PRLEN_SHFT ; 
 int RXEN ; 
 int RXFC ; 
 int /*<<< orphan*/  RXQ_EN ; 
 int RX_CHKSUM_EN ; 
 int SIMR ; 
 int SINGLE_PAUSE_MODE ; 
 int SPEED (int) ; 
 scalar_t__ SPEED_1000 ; 
 int SPEED_MASK ; 
 int TPAUSE ; 
 int TXEN ; 
 int TXFC ; 
 int /*<<< orphan*/  TXQ_EN ; 
 int VLAN_STRIP ; 
 int /*<<< orphan*/  emac_mac_mode_config (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_reg_update32 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void emac_mac_start(struct emac_adapter *adpt)
{
	struct phy_device *phydev = adpt->phydev;
	u32 mac, csr1;

	/* enable tx queue */
	emac_reg_update32(adpt->base + EMAC_TXQ_CTRL_0, 0, TXQ_EN);

	/* enable rx queue */
	emac_reg_update32(adpt->base + EMAC_RXQ_CTRL_0, 0, RXQ_EN);

	/* enable mac control */
	mac = readl(adpt->base + EMAC_MAC_CTRL);
	csr1 = readl(adpt->csr + EMAC_EMAC_WRAPPER_CSR1);

	mac |= TXEN | RXEN;     /* enable RX/TX */

	/* Configure MAC flow control. If set to automatic, then match
	 * whatever the PHY does. Otherwise, enable or disable it, depending
	 * on what the user configured via ethtool.
	 */
	mac &= ~(RXFC | TXFC);

	if (adpt->automatic) {
		/* If it's set to automatic, then update our local values */
		adpt->rx_flow_control = phydev->pause;
		adpt->tx_flow_control = phydev->pause != phydev->asym_pause;
	}
	mac |= adpt->rx_flow_control ? RXFC : 0;
	mac |= adpt->tx_flow_control ? TXFC : 0;

	/* setup link speed */
	mac &= ~SPEED_MASK;
	if (phydev->speed == SPEED_1000) {
		mac |= SPEED(2);
		csr1 |= FREQ_MODE;
	} else {
		mac |= SPEED(1);
		csr1 &= ~FREQ_MODE;
	}

	if (phydev->duplex == DUPLEX_FULL)
		mac |= FULLD;
	else
		mac &= ~FULLD;

	/* other parameters */
	mac |= (CRCE | PCRCE);
	mac |= ((adpt->preamble << PRLEN_SHFT) & PRLEN_BMSK);
	mac |= BROAD_EN;
	mac |= FLCHK;
	mac &= ~RX_CHKSUM_EN;
	mac &= ~(HUGEN | VLAN_STRIP | TPAUSE | SIMR | HUGE | MULTI_ALL |
		 DEBUG_MODE | SINGLE_PAUSE_MODE);

	/* Enable single-pause-frame mode if requested.
	 *
	 * If enabled, the EMAC will send a single pause frame when the RX
	 * queue is full.  This normally leads to packet loss because
	 * the pause frame disables the remote MAC only for 33ms (the quanta),
	 * and then the remote MAC continues sending packets even though
	 * the RX queue is still full.
	 *
	 * If disabled, the EMAC sends a pause frame every 31ms until the RX
	 * queue is no longer full.  Normally, this is the preferred
	 * method of operation.  However, when the system is hung (e.g.
	 * cores are halted), the EMAC interrupt handler is never called
	 * and so the RX queue fills up quickly and stays full.  The resuling
	 * non-stop "flood" of pause frames sometimes has the effect of
	 * disabling nearby switches.  In some cases, other nearby switches
	 * are also affected, shutting down the entire network.
	 *
	 * The user can enable or disable single-pause-frame mode
	 * via ethtool.
	 */
	mac |= adpt->single_pause_mode ? SINGLE_PAUSE_MODE : 0;

	writel_relaxed(csr1, adpt->csr + EMAC_EMAC_WRAPPER_CSR1);

	writel_relaxed(mac, adpt->base + EMAC_MAC_CTRL);

	/* enable interrupt read clear, low power sleep mode and
	 * the irq moderators
	 */

	writel_relaxed(adpt->irq_mod, adpt->base + EMAC_IRQ_MOD_TIM_INIT);
	writel_relaxed(INT_RD_CLR_EN | LPW_MODE | IRQ_MODERATOR_EN |
			IRQ_MODERATOR2_EN, adpt->base + EMAC_DMA_MAS_CTRL);

	emac_mac_mode_config(adpt);

	emac_reg_update32(adpt->base + EMAC_ATHR_HEADER_CTRL,
			  (HEADER_ENABLE | HEADER_CNT_EN), 0);
}