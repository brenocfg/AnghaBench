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
typedef  int ulong ;
typedef  int u32 ;
struct smsc911x_data {char* loopback_tx_pkt; int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  resetcount; scalar_t__ loopback_rx_pkt; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int BMCR_FULLDPLX ; 
 int BMCR_LOOPBACK ; 
 int EIO ; 
 int /*<<< orphan*/  HW_CFG ; 
 unsigned int HW_CFG_SF_ ; 
 unsigned int HW_CFG_TX_FIF_SZ_ ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAC_CR_FDPX_ ; 
 int MAC_CR_RXEN_ ; 
 int MAC_CR_TXEN_ ; 
 int /*<<< orphan*/  MII_BMCR ; 
 unsigned int MIN_PACKET_SIZE ; 
 int /*<<< orphan*/  RX_CFG ; 
 int /*<<< orphan*/  TX_CFG ; 
 int TX_CFG_TX_ON_ ; 
 int /*<<< orphan*/  eth_broadcast_addr (char*) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  smsc911x_mac_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc911x_mii_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ smsc911x_phy_check_loopbackpkt (struct smsc911x_data*) ; 
 int /*<<< orphan*/  smsc911x_phy_reset (struct smsc911x_data*) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int smsc911x_phy_loopbacktest(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	struct phy_device *phy_dev = dev->phydev;
	int result = -EIO;
	unsigned int i, val;
	unsigned long flags;

	/* Initialise tx packet using broadcast destination address */
	eth_broadcast_addr(pdata->loopback_tx_pkt);

	/* Use incrementing source address */
	for (i = 6; i < 12; i++)
		pdata->loopback_tx_pkt[i] = (char)i;

	/* Set length type field */
	pdata->loopback_tx_pkt[12] = 0x00;
	pdata->loopback_tx_pkt[13] = 0x00;

	for (i = 14; i < MIN_PACKET_SIZE; i++)
		pdata->loopback_tx_pkt[i] = (char)i;

	val = smsc911x_reg_read(pdata, HW_CFG);
	val &= HW_CFG_TX_FIF_SZ_;
	val |= HW_CFG_SF_;
	smsc911x_reg_write(pdata, HW_CFG, val);

	smsc911x_reg_write(pdata, TX_CFG, TX_CFG_TX_ON_);
	smsc911x_reg_write(pdata, RX_CFG,
		(u32)((ulong)pdata->loopback_rx_pkt & 0x03) << 8);

	for (i = 0; i < 10; i++) {
		/* Set PHY to 10/FD, no ANEG, and loopback mode */
		smsc911x_mii_write(phy_dev->mdio.bus, phy_dev->mdio.addr,
				   MII_BMCR, BMCR_LOOPBACK | BMCR_FULLDPLX);

		/* Enable MAC tx/rx, FD */
		spin_lock_irqsave(&pdata->mac_lock, flags);
		smsc911x_mac_write(pdata, MAC_CR, MAC_CR_FDPX_
				   | MAC_CR_TXEN_ | MAC_CR_RXEN_);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);

		if (smsc911x_phy_check_loopbackpkt(pdata) == 0) {
			result = 0;
			break;
		}
		pdata->resetcount++;

		/* Disable MAC rx */
		spin_lock_irqsave(&pdata->mac_lock, flags);
		smsc911x_mac_write(pdata, MAC_CR, 0);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);

		smsc911x_phy_reset(pdata);
	}

	/* Disable MAC */
	spin_lock_irqsave(&pdata->mac_lock, flags);
	smsc911x_mac_write(pdata, MAC_CR, 0);
	spin_unlock_irqrestore(&pdata->mac_lock, flags);

	/* Cancel PHY loopback mode */
	smsc911x_mii_write(phy_dev->mdio.bus, phy_dev->mdio.addr, MII_BMCR, 0);

	smsc911x_reg_write(pdata, TX_CFG, 0);
	smsc911x_reg_write(pdata, RX_CFG, 0);

	return result;
}