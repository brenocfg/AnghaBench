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
typedef  scalar_t__ u32 ;
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {TYPE_1__** vif; scalar_t__ close; int /*<<< orphan*/  txq_thread_started; int /*<<< orphan*/  txq_event; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 scalar_t__ FLOW_CONTROL_LOWER_THRESHOLD ; 
 int WILC_TX_ERR_NO_BUF ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int wilc_wlan_handle_txq (struct net_device*,scalar_t__*) ; 

__attribute__((used)) static int linux_wlan_txq_task(void *vp)
{
	int ret;
	u32 txq_count;
	struct net_device *dev = vp;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wl = vif->wilc;

	complete(&wl->txq_thread_started);
	while (1) {
		wait_for_completion(&wl->txq_event);

		if (wl->close) {
			complete(&wl->txq_thread_started);

			while (!kthread_should_stop())
				schedule();
			break;
		}
		do {
			ret = wilc_wlan_handle_txq(dev, &txq_count);
			if (txq_count < FLOW_CONTROL_LOWER_THRESHOLD) {
				if (netif_queue_stopped(wl->vif[0]->ndev))
					netif_wake_queue(wl->vif[0]->ndev);
				if (netif_queue_stopped(wl->vif[1]->ndev))
					netif_wake_queue(wl->vif[1]->ndev);
			}
		} while (ret == WILC_TX_ERR_NO_BUF && !wl->close);
	}
	return 0;
}