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
struct wilc_priv {int p2p_listen_state; int /*<<< orphan*/  hif_drv; int /*<<< orphan*/  scan_req_lock; } ;
struct net_device {int /*<<< orphan*/  ieee80211_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  aging_timer ; 
 int /*<<< orphan*/  clear_during_ip ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 scalar_t__ op_ifcs ; 
 int /*<<< orphan*/  remove_network_from_shadow ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wilc_priv* wdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_during_ip_timer ; 
 int wilc_init (struct net_device*,int /*<<< orphan*/ *) ; 

int wilc_init_host_int(struct net_device *net)
{
	int ret;
	struct wilc_priv *priv = wdev_priv(net->ieee80211_ptr);

	if (op_ifcs == 0) {
		timer_setup(&aging_timer, remove_network_from_shadow, 0);
		timer_setup(&wilc_during_ip_timer, clear_during_ip, 0);
	}
	op_ifcs++;

	priv->p2p_listen_state = false;

	mutex_init(&priv->scan_req_lock);
	ret = wilc_init(net, &priv->hif_drv);
	if (ret)
		netdev_err(net, "Error while initializing hostinterface\n");

	return ret;
}