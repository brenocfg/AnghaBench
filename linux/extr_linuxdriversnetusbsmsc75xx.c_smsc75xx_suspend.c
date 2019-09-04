#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct mii_if_info {int /*<<< orphan*/  phy_id; } ;
struct usbnet {int /*<<< orphan*/  net; struct mii_if_info mii; scalar_t__* data; } ;
struct usb_interface {int dummy; } ;
struct smsc75xx_priv {int wolopts; scalar_t__ suspend_flags; } ;
struct TYPE_5__ {scalar_t__ event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 scalar_t__ MAC_RX ; 
 int MAC_RX_RXEN ; 
 int MODE_CTRL_STS_EDPWRDOWN ; 
 int PHY_INT_MASK_ANEG_COMP ; 
 int PHY_INT_MASK_LINK_DOWN ; 
 int /*<<< orphan*/  PHY_MODE_CTRL_STS ; 
 scalar_t__ PMSG_IS_AUTO (TYPE_1__) ; 
 scalar_t__ PMT_CTL ; 
 int PMT_CTL_ED_EN ; 
 int PMT_CTL_WOL_EN ; 
 int PMT_CTL_WUPS ; 
 int PMT_CTL_WUPS_ED ; 
 scalar_t__ PM_EVENT_AUTO_SUSPEND ; 
 int SUPPORTED_WAKE ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 scalar_t__ WUCSR ; 
 int WUCSR_BCAST_FR ; 
 int WUCSR_BCST_EN ; 
 int WUCSR_MPEN ; 
 int WUCSR_MPR ; 
 int WUCSR_PFDA_EN ; 
 int WUCSR_WUEN ; 
 int WUCSR_WUFR ; 
 scalar_t__ WUF_CFGX ; 
 int WUF_CFGX_ATYPE_ALL ; 
 int WUF_CFGX_ATYPE_MULTICAST ; 
 int WUF_CFGX_EN ; 
 int WUF_NUM ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int smsc75xx_autosuspend (struct usbnet*,int) ; 
 int smsc75xx_enable_phy_wakeup_interrupts (struct usbnet*,int) ; 
 int smsc75xx_enter_suspend0 (struct usbnet*) ; 
 int smsc75xx_enter_suspend1 (struct usbnet*) ; 
 int smsc75xx_enter_suspend2 (struct usbnet*) ; 
 int smsc75xx_link_ok_nopm (struct usbnet*) ; 
 int smsc75xx_mdio_read_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc75xx_mdio_write_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int smsc75xx_read_reg_nopm (struct usbnet*,scalar_t__,int*) ; 
 int smsc75xx_write_reg_nopm (struct usbnet*,scalar_t__,int) ; 
 int smsc75xx_write_wuff (struct usbnet*,int /*<<< orphan*/ ,int,int) ; 
 int smsc_crc (int const*,int) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbnet_resume (struct usb_interface*) ; 
 int usbnet_suspend (struct usb_interface*,TYPE_1__) ; 

__attribute__((used)) static int smsc75xx_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct usbnet *dev = usb_get_intfdata(intf);
	struct smsc75xx_priv *pdata = (struct smsc75xx_priv *)(dev->data[0]);
	u32 val, link_up;
	int ret;

	ret = usbnet_suspend(intf, message);
	if (ret < 0) {
		netdev_warn(dev->net, "usbnet_suspend error\n");
		return ret;
	}

	if (pdata->suspend_flags) {
		netdev_warn(dev->net, "error during last resume\n");
		pdata->suspend_flags = 0;
	}

	/* determine if link is up using only _nopm functions */
	link_up = smsc75xx_link_ok_nopm(dev);

	if (message.event == PM_EVENT_AUTO_SUSPEND) {
		ret = smsc75xx_autosuspend(dev, link_up);
		goto done;
	}

	/* if we get this far we're not autosuspending */
	/* if no wol options set, or if link is down and we're not waking on
	 * PHY activity, enter lowest power SUSPEND2 mode
	 */
	if (!(pdata->wolopts & SUPPORTED_WAKE) ||
		!(link_up || (pdata->wolopts & WAKE_PHY))) {
		netdev_info(dev->net, "entering SUSPEND2 mode\n");

		/* disable energy detect (link up) & wake up events */
		ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading WUCSR\n");
			goto done;
		}

		val &= ~(WUCSR_MPEN | WUCSR_WUEN);

		ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing WUCSR\n");
			goto done;
		}

		ret = smsc75xx_read_reg_nopm(dev, PMT_CTL, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading PMT_CTL\n");
			goto done;
		}

		val &= ~(PMT_CTL_ED_EN | PMT_CTL_WOL_EN);

		ret = smsc75xx_write_reg_nopm(dev, PMT_CTL, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing PMT_CTL\n");
			goto done;
		}

		ret = smsc75xx_enter_suspend2(dev);
		goto done;
	}

	if (pdata->wolopts & WAKE_PHY) {
		ret = smsc75xx_enable_phy_wakeup_interrupts(dev,
			(PHY_INT_MASK_ANEG_COMP | PHY_INT_MASK_LINK_DOWN));
		if (ret < 0) {
			netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
			goto done;
		}

		/* if link is down then configure EDPD and enter SUSPEND1,
		 * otherwise enter SUSPEND0 below
		 */
		if (!link_up) {
			struct mii_if_info *mii = &dev->mii;
			netdev_info(dev->net, "entering SUSPEND1 mode\n");

			/* enable energy detect power-down mode */
			ret = smsc75xx_mdio_read_nopm(dev->net, mii->phy_id,
				PHY_MODE_CTRL_STS);
			if (ret < 0) {
				netdev_warn(dev->net, "Error reading PHY_MODE_CTRL_STS\n");
				goto done;
			}

			ret |= MODE_CTRL_STS_EDPWRDOWN;

			smsc75xx_mdio_write_nopm(dev->net, mii->phy_id,
				PHY_MODE_CTRL_STS, ret);

			/* enter SUSPEND1 mode */
			ret = smsc75xx_enter_suspend1(dev);
			goto done;
		}
	}

	if (pdata->wolopts & (WAKE_MCAST | WAKE_ARP)) {
		int i, filter = 0;

		/* disable all filters */
		for (i = 0; i < WUF_NUM; i++) {
			ret = smsc75xx_write_reg_nopm(dev, WUF_CFGX + i * 4, 0);
			if (ret < 0) {
				netdev_warn(dev->net, "Error writing WUF_CFGX\n");
				goto done;
			}
		}

		if (pdata->wolopts & WAKE_MCAST) {
			const u8 mcast[] = {0x01, 0x00, 0x5E};
			netdev_info(dev->net, "enabling multicast detection\n");

			val = WUF_CFGX_EN | WUF_CFGX_ATYPE_MULTICAST
				| smsc_crc(mcast, 3);
			ret = smsc75xx_write_wuff(dev, filter++, val, 0x0007);
			if (ret < 0) {
				netdev_warn(dev->net, "Error writing wakeup filter\n");
				goto done;
			}
		}

		if (pdata->wolopts & WAKE_ARP) {
			const u8 arp[] = {0x08, 0x06};
			netdev_info(dev->net, "enabling ARP detection\n");

			val = WUF_CFGX_EN | WUF_CFGX_ATYPE_ALL | (0x0C << 16)
				| smsc_crc(arp, 2);
			ret = smsc75xx_write_wuff(dev, filter++, val, 0x0003);
			if (ret < 0) {
				netdev_warn(dev->net, "Error writing wakeup filter\n");
				goto done;
			}
		}

		/* clear any pending pattern match packet status */
		ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading WUCSR\n");
			goto done;
		}

		val |= WUCSR_WUFR;

		ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing WUCSR\n");
			goto done;
		}

		netdev_info(dev->net, "enabling packet match detection\n");
		ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading WUCSR\n");
			goto done;
		}

		val |= WUCSR_WUEN;

		ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing WUCSR\n");
			goto done;
		}
	} else {
		netdev_info(dev->net, "disabling packet match detection\n");
		ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading WUCSR\n");
			goto done;
		}

		val &= ~WUCSR_WUEN;

		ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing WUCSR\n");
			goto done;
		}
	}

	/* disable magic, bcast & unicast wakeup sources */
	ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
	if (ret < 0) {
		netdev_warn(dev->net, "Error reading WUCSR\n");
		goto done;
	}

	val &= ~(WUCSR_MPEN | WUCSR_BCST_EN | WUCSR_PFDA_EN);

	ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
	if (ret < 0) {
		netdev_warn(dev->net, "Error writing WUCSR\n");
		goto done;
	}

	if (pdata->wolopts & WAKE_PHY) {
		netdev_info(dev->net, "enabling PHY wakeup\n");

		ret = smsc75xx_read_reg_nopm(dev, PMT_CTL, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading PMT_CTL\n");
			goto done;
		}

		/* clear wol status, enable energy detection */
		val &= ~PMT_CTL_WUPS;
		val |= (PMT_CTL_WUPS_ED | PMT_CTL_ED_EN);

		ret = smsc75xx_write_reg_nopm(dev, PMT_CTL, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing PMT_CTL\n");
			goto done;
		}
	}

	if (pdata->wolopts & WAKE_MAGIC) {
		netdev_info(dev->net, "enabling magic packet wakeup\n");
		ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading WUCSR\n");
			goto done;
		}

		/* clear any pending magic packet status */
		val |= WUCSR_MPR | WUCSR_MPEN;

		ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing WUCSR\n");
			goto done;
		}
	}

	if (pdata->wolopts & WAKE_BCAST) {
		netdev_info(dev->net, "enabling broadcast detection\n");
		ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading WUCSR\n");
			goto done;
		}

		val |= WUCSR_BCAST_FR | WUCSR_BCST_EN;

		ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing WUCSR\n");
			goto done;
		}
	}

	if (pdata->wolopts & WAKE_UCAST) {
		netdev_info(dev->net, "enabling unicast detection\n");
		ret = smsc75xx_read_reg_nopm(dev, WUCSR, &val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error reading WUCSR\n");
			goto done;
		}

		val |= WUCSR_WUFR | WUCSR_PFDA_EN;

		ret = smsc75xx_write_reg_nopm(dev, WUCSR, val);
		if (ret < 0) {
			netdev_warn(dev->net, "Error writing WUCSR\n");
			goto done;
		}
	}

	/* enable receiver to enable frame reception */
	ret = smsc75xx_read_reg_nopm(dev, MAC_RX, &val);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to read MAC_RX: %d\n", ret);
		goto done;
	}

	val |= MAC_RX_RXEN;

	ret = smsc75xx_write_reg_nopm(dev, MAC_RX, val);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to write MAC_RX: %d\n", ret);
		goto done;
	}

	/* some wol options are enabled, so enter SUSPEND0 */
	netdev_info(dev->net, "entering SUSPEND0 mode\n");
	ret = smsc75xx_enter_suspend0(dev);

done:
	/*
	 * TODO: resume() might need to handle the suspend failure
	 * in system sleep
	 */
	if (ret && PMSG_IS_AUTO(message))
		usbnet_resume(intf);
	return ret;
}