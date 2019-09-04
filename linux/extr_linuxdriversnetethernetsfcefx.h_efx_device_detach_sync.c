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
struct net_device {int dummy; } ;
struct efx_nic {struct net_device* net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 

__attribute__((used)) static inline void efx_device_detach_sync(struct efx_nic *efx)
{
	struct net_device *dev = efx->net_dev;

	/* Lock/freeze all TX queues so that we can be sure the
	 * TX scheduler is stopped when we're done and before
	 * netif_device_present() becomes false.
	 */
	netif_tx_lock_bh(dev);
	netif_device_detach(dev);
	netif_tx_unlock_bh(dev);
}