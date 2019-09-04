#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {scalar_t__ of_node; } ;
struct TYPE_11__ {TYPE_4__ dev; } ;
struct phy_device {int is_internal; scalar_t__ irq; int advertising; int /*<<< orphan*/  autoneg; TYPE_5__ mdio; int /*<<< orphan*/  supported; int /*<<< orphan*/  mdix; } ;
struct TYPE_7__ {scalar_t__ phyirq; } ;
struct lan78xx_net {int chipid; int fc_request_control; int /*<<< orphan*/  fc_autoneg; int /*<<< orphan*/  net; TYPE_3__* udev; TYPE_6__* mdiobus; int /*<<< orphan*/  interface; TYPE_1__ domain_data; } ;
struct ethtool_eee {int advertised; int eee_enabled; int tx_lpi_enabled; int tx_lpi_timer; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  edata ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_9__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int EIO ; 
 int /*<<< orphan*/  ETHTOOL_SEEE ; 
 int /*<<< orphan*/  ETH_TP_MDI_AUTO ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  HW_CFG ; 
 int HW_CFG_LED0_EN_ ; 
 int HW_CFG_LED1_EN_ ; 
 int HW_CFG_LED2_EN_ ; 
 int HW_CFG_LED3_EN_ ; 
#define  ID_REV_CHIP_ID_7800_ 130 
#define  ID_REV_CHIP_ID_7801_ 129 
#define  ID_REV_CHIP_ID_7850_ 128 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  PHY_KSZ9031RNX ; 
 int /*<<< orphan*/  PHY_LAN8835 ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Half ; 
 int /*<<< orphan*/  fixed_phy_unregister (struct phy_device*) ; 
 int /*<<< orphan*/  genphy_config_aneg (struct phy_device*) ; 
 struct phy_device* lan7801_phy_init (struct lan78xx_net*) ; 
 int /*<<< orphan*/  lan78xx_link_status_change ; 
 int /*<<< orphan*/  lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lan78xx_set_eee (int /*<<< orphan*/ ,struct ethtool_eee*) ; 
 int /*<<< orphan*/  lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ethtool_eee*,int /*<<< orphan*/ ,int) ; 
 int mii_adv_to_ethtool_adv_t (int) ; 
 int /*<<< orphan*/  mii_advertise_flowctrl (int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int of_property_count_elems_of_size (scalar_t__,char*,int) ; 
 scalar_t__ of_property_read_bool (scalar_t__,char*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int phy_connect_direct (int /*<<< orphan*/ ,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (TYPE_6__*) ; 
 scalar_t__ phy_is_pseudo_fixed_link (struct phy_device*) ; 
 int /*<<< orphan*/  phy_unregister_fixup_for_uid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan78xx_phy_init(struct lan78xx_net *dev)
{
	int ret;
	u32 mii_adv;
	struct phy_device *phydev;

	switch (dev->chipid) {
	case ID_REV_CHIP_ID_7801_:
		phydev = lan7801_phy_init(dev);
		if (!phydev) {
			netdev_err(dev->net, "lan7801: PHY Init Failed");
			return -EIO;
		}
		break;

	case ID_REV_CHIP_ID_7800_:
	case ID_REV_CHIP_ID_7850_:
		phydev = phy_find_first(dev->mdiobus);
		if (!phydev) {
			netdev_err(dev->net, "no PHY found\n");
			return -EIO;
		}
		phydev->is_internal = true;
		dev->interface = PHY_INTERFACE_MODE_GMII;
		break;

	default:
		netdev_err(dev->net, "Unknown CHIP ID found\n");
		return -EIO;
	}

	/* if phyirq is not set, use polling mode in phylib */
	if (dev->domain_data.phyirq > 0)
		phydev->irq = dev->domain_data.phyirq;
	else
		phydev->irq = 0;
	netdev_dbg(dev->net, "phydev->irq = %d\n", phydev->irq);

	/* set to AUTOMDIX */
	phydev->mdix = ETH_TP_MDI_AUTO;

	ret = phy_connect_direct(dev->net, phydev,
				 lan78xx_link_status_change,
				 dev->interface);
	if (ret) {
		netdev_err(dev->net, "can't attach PHY to %s\n",
			   dev->mdiobus->id);
		if (dev->chipid == ID_REV_CHIP_ID_7801_) {
			if (phy_is_pseudo_fixed_link(phydev)) {
				fixed_phy_unregister(phydev);
			} else {
				phy_unregister_fixup_for_uid(PHY_KSZ9031RNX,
							     0xfffffff0);
				phy_unregister_fixup_for_uid(PHY_LAN8835,
							     0xfffffff0);
			}
		}
		return -EIO;
	}

	/* MAC doesn't support 1000T Half */
	phydev->supported &= ~SUPPORTED_1000baseT_Half;

	/* support both flow controls */
	dev->fc_request_control = (FLOW_CTRL_RX | FLOW_CTRL_TX);
	phydev->advertising &= ~(ADVERTISED_Pause | ADVERTISED_Asym_Pause);
	mii_adv = (u32)mii_advertise_flowctrl(dev->fc_request_control);
	phydev->advertising |= mii_adv_to_ethtool_adv_t(mii_adv);

	if (of_property_read_bool(phydev->mdio.dev.of_node,
				  "microchip,eee-enabled")) {
		struct ethtool_eee edata;
		memset(&edata, 0, sizeof(edata));
		edata.cmd = ETHTOOL_SEEE;
		edata.advertised = ADVERTISED_1000baseT_Full |
				   ADVERTISED_100baseT_Full;
		edata.eee_enabled = true;
		edata.tx_lpi_enabled = true;
		if (of_property_read_u32(dev->udev->dev.of_node,
					 "microchip,tx-lpi-timer",
					 &edata.tx_lpi_timer))
			edata.tx_lpi_timer = 600; /* non-aggressive */
		(void)lan78xx_set_eee(dev->net, &edata);
	}

	if (phydev->mdio.dev.of_node) {
		u32 reg;
		int len;

		len = of_property_count_elems_of_size(phydev->mdio.dev.of_node,
						      "microchip,led-modes",
						      sizeof(u32));
		if (len >= 0) {
			/* Ensure the appropriate LEDs are enabled */
			lan78xx_read_reg(dev, HW_CFG, &reg);
			reg &= ~(HW_CFG_LED0_EN_ |
				 HW_CFG_LED1_EN_ |
				 HW_CFG_LED2_EN_ |
				 HW_CFG_LED3_EN_);
			reg |= (len > 0) * HW_CFG_LED0_EN_ |
				(len > 1) * HW_CFG_LED1_EN_ |
				(len > 2) * HW_CFG_LED2_EN_ |
				(len > 3) * HW_CFG_LED3_EN_;
			lan78xx_write_reg(dev, HW_CFG, reg);
		}
	}

	genphy_config_aneg(phydev);

	dev->fc_autoneg = phydev->autoneg;

	return 0;
}