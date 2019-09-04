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
struct efx_nic {scalar_t__ state; int /*<<< orphan*/  stats_lock; TYPE_2__* type; int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  workqueue; scalar_t__ reset_pending; int /*<<< orphan*/  net_dev; scalar_t__ port_enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_stats ) (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pull_stats ) (struct efx_nic*) ;int /*<<< orphan*/  (* start_stats ) (struct efx_nic*) ;int /*<<< orphan*/ * monitor; } ;
struct TYPE_3__ {scalar_t__ (* poll ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_ASSERT_RESET_SERIALISED (struct efx_nic*) ; 
 scalar_t__ STATE_DISABLED ; 
 int /*<<< orphan*/  efx_link_status_changed (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_monitor_interval ; 
 int /*<<< orphan*/  efx_start_datapath (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_start_port (struct efx_nic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct efx_nic*) ; 
 int /*<<< orphan*/  stub2 (struct efx_nic*) ; 
 int /*<<< orphan*/  stub3 (struct efx_nic*) ; 
 int /*<<< orphan*/  stub4 (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_start_all(struct efx_nic *efx)
{
	EFX_ASSERT_RESET_SERIALISED(efx);
	BUG_ON(efx->state == STATE_DISABLED);

	/* Check that it is appropriate to restart the interface. All
	 * of these flags are safe to read under just the rtnl lock */
	if (efx->port_enabled || !netif_running(efx->net_dev) ||
	    efx->reset_pending)
		return;

	efx_start_port(efx);
	efx_start_datapath(efx);

	/* Start the hardware monitor if there is one */
	if (efx->type->monitor != NULL)
		queue_delayed_work(efx->workqueue, &efx->monitor_work,
				   efx_monitor_interval);

	/* Link state detection is normally event-driven; we have
	 * to poll now because we could have missed a change
	 */
	mutex_lock(&efx->mac_lock);
	if (efx->phy_op->poll(efx))
		efx_link_status_changed(efx);
	mutex_unlock(&efx->mac_lock);

	efx->type->start_stats(efx);
	efx->type->pull_stats(efx);
	spin_lock_bh(&efx->stats_lock);
	efx->type->update_stats(efx, NULL, NULL);
	spin_unlock_bh(&efx->stats_lock);
}