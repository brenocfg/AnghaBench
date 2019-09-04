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
struct wilc {int /*<<< orphan*/  txq_thread_started; int /*<<< orphan*/  sync_event; int /*<<< orphan*/  cfg_event; int /*<<< orphan*/  txq_event; int /*<<< orphan*/  txq_add_to_head_cs; int /*<<< orphan*/  txq_spinlock; int /*<<< orphan*/  rxq_cs; int /*<<< orphan*/  hif_cs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wlan_init_locks(struct net_device *dev)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wl = vif->wilc;

	mutex_init(&wl->hif_cs);
	mutex_init(&wl->rxq_cs);

	spin_lock_init(&wl->txq_spinlock);
	mutex_init(&wl->txq_add_to_head_cs);

	init_completion(&wl->txq_event);

	init_completion(&wl->cfg_event);
	init_completion(&wl->sync_event);
	init_completion(&wl->txq_thread_started);

	return 0;
}