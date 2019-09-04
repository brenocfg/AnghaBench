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
struct TYPE_2__ {scalar_t__ irq_type; scalar_t__ irq_polarity; } ;
struct smsc911x_data {int last_duplex; int last_carrier; int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  napi; scalar_t__ ioaddr; scalar_t__ software_irq_signal; TYPE_1__ config; } ;
struct net_device {int /*<<< orphan*/ * phydev; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFC_CFG ; 
 int /*<<< orphan*/  E2P_CMD ; 
 unsigned int E2P_CMD_EPC_BUSY_ ; 
 int ENODEV ; 
 unsigned int ETH_P_8021Q ; 
 int /*<<< orphan*/  FIFO_INT ; 
 unsigned int FIFO_INT_RX_STS_LEVEL_ ; 
 unsigned int FIFO_INT_TX_AVAIL_LEVEL_ ; 
 int /*<<< orphan*/  GPIO_CFG ; 
 int /*<<< orphan*/  HW_CFG ; 
 unsigned int HW_CFG_SF_ ; 
 int HW_CFG_TX_FIF_SZ_ ; 
 int /*<<< orphan*/  INT_CFG ; 
 int INT_CFG_IRQ_EN_ ; 
 unsigned int INT_CFG_IRQ_POL_ ; 
 unsigned int INT_CFG_IRQ_TYPE_ ; 
 int /*<<< orphan*/  INT_EN ; 
 unsigned int INT_EN_RSFL_EN_ ; 
 unsigned int INT_EN_RXSTOP_INT_EN_ ; 
 unsigned int INT_EN_SW_INT_EN_ ; 
 unsigned int INT_EN_TDFA_EN_ ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  MAC_CR ; 
 unsigned int MAC_CR_HBDIS_ ; 
 unsigned int MAC_CR_RXEN_ ; 
 unsigned int MAC_CR_TXEN_ ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  RX_CFG ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TX_CFG ; 
 unsigned int TX_CFG_TX_ON_ ; 
 int /*<<< orphan*/  VLAN1 ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  ifup ; 
 int irq_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  smsc911x_disable_irq_chip (struct net_device*) ; 
 int /*<<< orphan*/  smsc911x_irqhandler ; 
 unsigned int smsc911x_mac_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_mac_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int smsc911x_mii_probe (struct net_device*) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smsc911x_set_hw_mac_address (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int smsc911x_soft_reset (struct smsc911x_data*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int smsc911x_open(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	unsigned int timeout;
	unsigned int temp;
	unsigned int intcfg;
	int retval;
	int irq_flags;

	/* find and start the given phy */
	if (!dev->phydev) {
		retval = smsc911x_mii_probe(dev);
		if (retval < 0) {
			SMSC_WARN(pdata, probe, "Error starting phy");
			goto out;
		}
	}

	/* Reset the LAN911x */
	retval = smsc911x_soft_reset(pdata);
	if (retval) {
		SMSC_WARN(pdata, hw, "soft reset failed");
		goto mii_free_out;
	}

	smsc911x_reg_write(pdata, HW_CFG, 0x00050000);
	smsc911x_reg_write(pdata, AFC_CFG, 0x006E3740);

	/* Increase the legal frame size of VLAN tagged frames to 1522 bytes */
	spin_lock_irq(&pdata->mac_lock);
	smsc911x_mac_write(pdata, VLAN1, ETH_P_8021Q);
	spin_unlock_irq(&pdata->mac_lock);

	/* Make sure EEPROM has finished loading before setting GPIO_CFG */
	timeout = 50;
	while ((smsc911x_reg_read(pdata, E2P_CMD) & E2P_CMD_EPC_BUSY_) &&
	       --timeout) {
		udelay(10);
	}

	if (unlikely(timeout == 0))
		SMSC_WARN(pdata, ifup,
			  "Timed out waiting for EEPROM busy bit to clear");

	smsc911x_reg_write(pdata, GPIO_CFG, 0x70070000);

	/* The soft reset above cleared the device's MAC address,
	 * restore it from local copy (set in probe) */
	spin_lock_irq(&pdata->mac_lock);
	smsc911x_set_hw_mac_address(pdata, dev->dev_addr);
	spin_unlock_irq(&pdata->mac_lock);

	/* Initialise irqs, but leave all sources disabled */
	smsc911x_disable_irq_chip(dev);

	/* Set interrupt deassertion to 100uS */
	intcfg = ((10 << 24) | INT_CFG_IRQ_EN_);

	if (pdata->config.irq_polarity) {
		SMSC_TRACE(pdata, ifup, "irq polarity: active high");
		intcfg |= INT_CFG_IRQ_POL_;
	} else {
		SMSC_TRACE(pdata, ifup, "irq polarity: active low");
	}

	if (pdata->config.irq_type) {
		SMSC_TRACE(pdata, ifup, "irq type: push-pull");
		intcfg |= INT_CFG_IRQ_TYPE_;
	} else {
		SMSC_TRACE(pdata, ifup, "irq type: open drain");
	}

	smsc911x_reg_write(pdata, INT_CFG, intcfg);

	SMSC_TRACE(pdata, ifup, "Testing irq handler using IRQ %d", dev->irq);
	pdata->software_irq_signal = 0;
	smp_wmb();

	irq_flags = irq_get_trigger_type(dev->irq);
	retval = request_irq(dev->irq, smsc911x_irqhandler,
			     irq_flags | IRQF_SHARED, dev->name, dev);
	if (retval) {
		SMSC_WARN(pdata, probe,
			  "Unable to claim requested irq: %d", dev->irq);
		goto mii_free_out;
	}

	temp = smsc911x_reg_read(pdata, INT_EN);
	temp |= INT_EN_SW_INT_EN_;
	smsc911x_reg_write(pdata, INT_EN, temp);

	timeout = 1000;
	while (timeout--) {
		if (pdata->software_irq_signal)
			break;
		msleep(1);
	}

	if (!pdata->software_irq_signal) {
		netdev_warn(dev, "ISR failed signaling test (IRQ %d)\n",
			    dev->irq);
		retval = -ENODEV;
		goto irq_stop_out;
	}
	SMSC_TRACE(pdata, ifup, "IRQ handler passed test using IRQ %d",
		   dev->irq);

	netdev_info(dev, "SMSC911x/921x identified at %#08lx, IRQ: %d\n",
		    (unsigned long)pdata->ioaddr, dev->irq);

	/* Reset the last known duplex and carrier */
	pdata->last_duplex = -1;
	pdata->last_carrier = -1;

	/* Bring the PHY up */
	phy_start(dev->phydev);

	temp = smsc911x_reg_read(pdata, HW_CFG);
	/* Preserve TX FIFO size and external PHY configuration */
	temp &= (HW_CFG_TX_FIF_SZ_|0x00000FFF);
	temp |= HW_CFG_SF_;
	smsc911x_reg_write(pdata, HW_CFG, temp);

	temp = smsc911x_reg_read(pdata, FIFO_INT);
	temp |= FIFO_INT_TX_AVAIL_LEVEL_;
	temp &= ~(FIFO_INT_RX_STS_LEVEL_);
	smsc911x_reg_write(pdata, FIFO_INT, temp);

	/* set RX Data offset to 2 bytes for alignment */
	smsc911x_reg_write(pdata, RX_CFG, (NET_IP_ALIGN << 8));

	/* enable NAPI polling before enabling RX interrupts */
	napi_enable(&pdata->napi);

	temp = smsc911x_reg_read(pdata, INT_EN);
	temp |= (INT_EN_TDFA_EN_ | INT_EN_RSFL_EN_ | INT_EN_RXSTOP_INT_EN_);
	smsc911x_reg_write(pdata, INT_EN, temp);

	spin_lock_irq(&pdata->mac_lock);
	temp = smsc911x_mac_read(pdata, MAC_CR);
	temp |= (MAC_CR_TXEN_ | MAC_CR_RXEN_ | MAC_CR_HBDIS_);
	smsc911x_mac_write(pdata, MAC_CR, temp);
	spin_unlock_irq(&pdata->mac_lock);

	smsc911x_reg_write(pdata, TX_CFG, TX_CFG_TX_ON_);

	netif_start_queue(dev);
	return 0;

irq_stop_out:
	free_irq(dev->irq, dev);
mii_free_out:
	phy_disconnect(dev->phydev);
	dev->phydev = NULL;
out:
	return retval;
}