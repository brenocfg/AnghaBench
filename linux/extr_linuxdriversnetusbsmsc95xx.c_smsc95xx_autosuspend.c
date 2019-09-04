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
typedef  int /*<<< orphan*/  u32 ;
struct usbnet {int /*<<< orphan*/  net; scalar_t__* data; } ;
struct smsc95xx_priv {int features; } ;

/* Variables and functions */
 int EBUSY ; 
 int FEATURE_PHY_NLP_CROSSOVER ; 
 int /*<<< orphan*/  PHY_INT_MASK_ANEG_COMP_ ; 
 int /*<<< orphan*/  PHY_INT_MASK_LINK_DOWN_ ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int smsc95xx_enable_phy_wakeup_interrupts (struct usbnet*,int /*<<< orphan*/ ) ; 
 int smsc95xx_enter_suspend1 (struct usbnet*) ; 
 int smsc95xx_enter_suspend2 (struct usbnet*) ; 
 int smsc95xx_enter_suspend3 (struct usbnet*) ; 

__attribute__((used)) static int smsc95xx_autosuspend(struct usbnet *dev, u32 link_up)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);
	int ret;

	if (!netif_running(dev->net)) {
		/* interface is ifconfig down so fully power down hw */
		netdev_dbg(dev->net, "autosuspend entering SUSPEND2\n");
		return smsc95xx_enter_suspend2(dev);
	}

	if (!link_up) {
		/* link is down so enter EDPD mode, but only if device can
		 * reliably resume from it.  This check should be redundant
		 * as current FEATURE_REMOTE_WAKEUP parts also support
		 * FEATURE_PHY_NLP_CROSSOVER but it's included for clarity */
		if (!(pdata->features & FEATURE_PHY_NLP_CROSSOVER)) {
			netdev_warn(dev->net, "EDPD not supported\n");
			return -EBUSY;
		}

		netdev_dbg(dev->net, "autosuspend entering SUSPEND1\n");

		/* enable PHY wakeup events for if cable is attached */
		ret = smsc95xx_enable_phy_wakeup_interrupts(dev,
			PHY_INT_MASK_ANEG_COMP_);
		if (ret < 0) {
			netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
			return ret;
		}

		netdev_info(dev->net, "entering SUSPEND1 mode\n");
		return smsc95xx_enter_suspend1(dev);
	}

	/* enable PHY wakeup events so we remote wakeup if cable is pulled */
	ret = smsc95xx_enable_phy_wakeup_interrupts(dev,
		PHY_INT_MASK_LINK_DOWN_);
	if (ret < 0) {
		netdev_warn(dev->net, "error enabling PHY wakeup ints\n");
		return ret;
	}

	netdev_dbg(dev->net, "autosuspend entering SUSPEND3\n");
	return smsc95xx_enter_suspend3(dev);
}