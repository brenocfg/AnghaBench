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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {int close; int /*<<< orphan*/ * txq_thread; int /*<<< orphan*/  txq_event; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void wlan_deinitialize_threads(struct net_device *dev)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wl = vif->wilc;

	wl->close = 1;

	complete(&wl->txq_event);

	if (wl->txq_thread) {
		kthread_stop(wl->txq_thread);
		wl->txq_thread = NULL;
	}
}