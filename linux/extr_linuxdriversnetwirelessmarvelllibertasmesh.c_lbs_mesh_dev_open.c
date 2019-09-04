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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  tx_pending_len; TYPE_1__* wdev; int /*<<< orphan*/  iface_running; } ;
struct TYPE_2__ {scalar_t__ iftype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_MESH_CONFIG_START ; 
 int EBUSY ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int lbs_mesh_config (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_mesh_get_channel (struct lbs_private*) ; 
 int lbs_start_iface (struct lbs_private*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_mesh_dev_open(struct net_device *dev)
{
	struct lbs_private *priv = dev->ml_priv;
	int ret = 0;

	if (!priv->iface_running) {
		ret = lbs_start_iface(priv);
		if (ret)
			goto out;
	}

	spin_lock_irq(&priv->driver_lock);

	if (priv->wdev->iftype == NL80211_IFTYPE_MONITOR) {
		ret = -EBUSY;
		spin_unlock_irq(&priv->driver_lock);
		goto out;
	}

	netif_carrier_on(dev);

	if (!priv->tx_pending_len)
		netif_wake_queue(dev);

	spin_unlock_irq(&priv->driver_lock);

	ret = lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START,
		lbs_mesh_get_channel(priv));

out:
	return ret;
}