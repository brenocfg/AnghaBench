#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xenvif {TYPE_1__* dev; int /*<<< orphan*/  status; int /*<<< orphan*/  can_sg; } ;
struct TYPE_4__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  VIF_STATUS_CONNECTED ; 
 int /*<<< orphan*/  dev_set_mtu (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_update_features (TYPE_1__*) ; 
 scalar_t__ netif_running (TYPE_1__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenvif_up (struct xenvif*) ; 

void xenvif_carrier_on(struct xenvif *vif)
{
	rtnl_lock();
	if (!vif->can_sg && vif->dev->mtu > ETH_DATA_LEN)
		dev_set_mtu(vif->dev, ETH_DATA_LEN);
	netdev_update_features(vif->dev);
	set_bit(VIF_STATUS_CONNECTED, &vif->status);
	if (netif_running(vif->dev))
		xenvif_up(vif);
	rtnl_unlock();
}