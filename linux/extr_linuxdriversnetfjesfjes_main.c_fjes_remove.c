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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct fjes_hw {int dummy; } ;
struct fjes_adapter {int /*<<< orphan*/  napi; scalar_t__ txrx_wq; scalar_t__ control_wq; int /*<<< orphan*/  tx_stall_task; int /*<<< orphan*/  raise_intr_rxdata_task; int /*<<< orphan*/  unshare_watch_task; int /*<<< orphan*/  interrupt_watch_task; struct fjes_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 struct net_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fjes_dbg_adapter_exit (struct fjes_adapter*) ; 
 int /*<<< orphan*/  fjes_hw_exit (struct fjes_hw*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int fjes_remove(struct platform_device *plat_dev)
{
	struct net_device *netdev = dev_get_drvdata(&plat_dev->dev);
	struct fjes_adapter *adapter = netdev_priv(netdev);
	struct fjes_hw *hw = &adapter->hw;

	fjes_dbg_adapter_exit(adapter);

	cancel_delayed_work_sync(&adapter->interrupt_watch_task);
	cancel_work_sync(&adapter->unshare_watch_task);
	cancel_work_sync(&adapter->raise_intr_rxdata_task);
	cancel_work_sync(&adapter->tx_stall_task);
	if (adapter->control_wq)
		destroy_workqueue(adapter->control_wq);
	if (adapter->txrx_wq)
		destroy_workqueue(adapter->txrx_wq);

	unregister_netdev(netdev);

	fjes_hw_exit(hw);

	netif_napi_del(&adapter->napi);

	free_netdev(netdev);

	return 0;
}