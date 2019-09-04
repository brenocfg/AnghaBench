#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct r8192_priv {TYPE_2__* rtllib; scalar_t__ polling_timer_on; int /*<<< orphan*/  gpio_change_rf_wq; int /*<<< orphan*/  gpio_polling_timer; } ;
struct pci_dev {int dummy; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_4__ {scalar_t__ bSupportRemoteWakeUp; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_GEN ; 
 int CPU_GEN_SYSTEM_RESET ; 
 int /*<<< orphan*/  MacBlkCtrl ; 
 int /*<<< orphan*/  PMR ; 
 int /*<<< orphan*/  RF_CHANGE_BY_INIT ; 
 int /*<<< orphan*/  WFCRC0 ; 
 int /*<<< orphan*/  WFCRC1 ; 
 int /*<<< orphan*/  WFCRC2 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eRfOff ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int rtl92e_readl (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_set_rf_state (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

int rtl92e_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct r8192_priv *priv = rtllib_priv(dev);
	u32	ulRegRead;

	netdev_info(dev, "============> r8192E suspend call.\n");
	del_timer_sync(&priv->gpio_polling_timer);
	cancel_delayed_work_sync(&priv->gpio_change_rf_wq);
	priv->polling_timer_on = 0;

	if (!netif_running(dev)) {
		netdev_info(dev,
			    "RTL819XE:UI is open out of suspend function\n");
		goto out_pci_suspend;
	}

	if (dev->netdev_ops->ndo_stop)
		dev->netdev_ops->ndo_stop(dev);
	netif_device_detach(dev);

	if (!priv->rtllib->bSupportRemoteWakeUp) {
		rtl92e_set_rf_state(dev, eRfOff, RF_CHANGE_BY_INIT);
		ulRegRead = rtl92e_readl(dev, CPU_GEN);
		ulRegRead |= CPU_GEN_SYSTEM_RESET;
		rtl92e_writel(dev, CPU_GEN, ulRegRead);
	} else {
		rtl92e_writel(dev, WFCRC0, 0xffffffff);
		rtl92e_writel(dev, WFCRC1, 0xffffffff);
		rtl92e_writel(dev, WFCRC2, 0xffffffff);
		rtl92e_writeb(dev, PMR, 0x5);
		rtl92e_writeb(dev, MacBlkCtrl, 0xa);
	}
out_pci_suspend:
	netdev_info(dev, "WOL is %s\n", priv->rtllib->bSupportRemoteWakeUp ?
			    "Supported" : "Not supported");
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_enable_wake(pdev, pci_choose_state(pdev, state),
			priv->rtllib->bSupportRemoteWakeUp ? 1 : 0);
	pci_set_power_state(pdev, pci_choose_state(pdev, state));

	mdelay(20);

	return 0;
}