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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int /*<<< orphan*/  driver_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_MESH_CONFIG_STOP ; 
 int /*<<< orphan*/  lbs_iface_active (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_mesh_config (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_mesh_get_channel (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_stop_iface (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_update_mcast (struct lbs_private*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_mesh_stop(struct net_device *dev)
{
	struct lbs_private *priv = dev->ml_priv;

	lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_STOP,
		lbs_mesh_get_channel(priv));

	spin_lock_irq(&priv->driver_lock);

	netif_stop_queue(dev);
	netif_carrier_off(dev);

	spin_unlock_irq(&priv->driver_lock);

	lbs_update_mcast(priv);
	if (!lbs_iface_active(priv))
		lbs_stop_iface(priv);

	return 0;
}