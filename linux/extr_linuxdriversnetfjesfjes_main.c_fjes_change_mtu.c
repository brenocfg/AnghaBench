#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int mtu; int /*<<< orphan*/  dev_addr; } ;
struct fjes_hw {int max_epid; int my_epid; int /*<<< orphan*/  rx_status_lock; TYPE_3__* ep_shm_info; } ;
struct fjes_adapter {int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_stall_task; struct fjes_hw hw; } ;
struct TYPE_8__ {TYPE_2__* info; } ;
struct TYPE_7__ {TYPE_4__ tx; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_status; } ;
struct TYPE_6__ {TYPE_1__ v1i; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FJES_RX_MTU_CHANGING_DONE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fjes_hw_setup_epbuf (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int* fjes_support_mtu ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fjes_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);
	bool running = netif_running(netdev);
	struct fjes_hw *hw = &adapter->hw;
	unsigned long flags;
	int ret = -EINVAL;
	int idx, epidx;

	for (idx = 0; fjes_support_mtu[idx] != 0; idx++) {
		if (new_mtu <= fjes_support_mtu[idx]) {
			new_mtu = fjes_support_mtu[idx];
			if (new_mtu == netdev->mtu)
				return 0;

			ret = 0;
			break;
		}
	}

	if (ret)
		return ret;

	if (running) {
		spin_lock_irqsave(&hw->rx_status_lock, flags);
		for (epidx = 0; epidx < hw->max_epid; epidx++) {
			if (epidx == hw->my_epid)
				continue;
			hw->ep_shm_info[epidx].tx.info->v1i.rx_status &=
				~FJES_RX_MTU_CHANGING_DONE;
		}
		spin_unlock_irqrestore(&hw->rx_status_lock, flags);

		netif_tx_stop_all_queues(netdev);
		netif_carrier_off(netdev);
		cancel_work_sync(&adapter->tx_stall_task);
		napi_disable(&adapter->napi);

		msleep(1000);

		netif_tx_stop_all_queues(netdev);
	}

	netdev->mtu = new_mtu;

	if (running) {
		for (epidx = 0; epidx < hw->max_epid; epidx++) {
			if (epidx == hw->my_epid)
				continue;

			spin_lock_irqsave(&hw->rx_status_lock, flags);
			fjes_hw_setup_epbuf(&hw->ep_shm_info[epidx].tx,
					    netdev->dev_addr,
					    netdev->mtu);

			hw->ep_shm_info[epidx].tx.info->v1i.rx_status |=
				FJES_RX_MTU_CHANGING_DONE;
			spin_unlock_irqrestore(&hw->rx_status_lock, flags);
		}

		netif_tx_wake_all_queues(netdev);
		netif_carrier_on(netdev);
		napi_enable(&adapter->napi);
		napi_schedule(&adapter->napi);
	}

	return ret;
}