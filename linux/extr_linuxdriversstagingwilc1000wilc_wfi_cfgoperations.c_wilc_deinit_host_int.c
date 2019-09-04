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
struct wilc_vif {int dummy; } ;
struct wilc_priv {int p2p_listen_state; int /*<<< orphan*/  scan_req_lock; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  ieee80211_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_shadow_scan () ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ op_ifcs ; 
 struct wilc_priv* wdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_deinit (struct wilc_vif*) ; 
 int /*<<< orphan*/  wilc_during_ip_timer ; 

int wilc_deinit_host_int(struct net_device *net)
{
	int ret;
	struct wilc_priv *priv = wdev_priv(net->ieee80211_ptr);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	priv->p2p_listen_state = false;

	op_ifcs--;

	mutex_destroy(&priv->scan_req_lock);
	ret = wilc_deinit(vif);

	clear_shadow_scan();
	if (op_ifcs == 0)
		del_timer_sync(&wilc_during_ip_timer);

	if (ret)
		netdev_err(net, "Error while deinitializing host interface\n");

	return ret;
}