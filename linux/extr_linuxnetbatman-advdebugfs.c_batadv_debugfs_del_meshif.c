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
struct net {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/ * debug_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_debug_log_cleanup (struct batadv_priv*) ; 
 scalar_t__ batadv_debugfs ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 struct net* dev_net (struct net_device*) ; 
 struct net init_net ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 

void batadv_debugfs_del_meshif(struct net_device *dev)
{
	struct batadv_priv *bat_priv = netdev_priv(dev);
	struct net *net = dev_net(dev);

	if (net != &init_net)
		return;

	batadv_debug_log_cleanup(bat_priv);

	if (batadv_debugfs) {
		debugfs_remove_recursive(bat_priv->debug_dir);
		bat_priv->debug_dir = NULL;
	}
}