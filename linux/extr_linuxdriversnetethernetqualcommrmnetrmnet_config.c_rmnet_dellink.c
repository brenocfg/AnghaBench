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
typedef  int /*<<< orphan*/  u8 ;
struct rmnet_priv {struct net_device* real_dev; } ;
struct rmnet_port {int dummy; } ;
struct rmnet_endpoint {int /*<<< orphan*/  hlnode; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rmnet_endpoint*) ; 
 struct rmnet_priv* netdev_priv (struct net_device*) ; 
 struct rmnet_endpoint* rmnet_get_endpoint (struct rmnet_port*,int /*<<< orphan*/ ) ; 
 struct rmnet_port* rmnet_get_port_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  rmnet_is_real_dev_registered (struct net_device*) ; 
 int /*<<< orphan*/  rmnet_unregister_bridge (struct net_device*,struct rmnet_port*) ; 
 int /*<<< orphan*/  rmnet_unregister_real_device (struct net_device*,struct rmnet_port*) ; 
 int /*<<< orphan*/  rmnet_vnd_dellink (int /*<<< orphan*/ ,struct rmnet_port*,struct rmnet_endpoint*) ; 
 int /*<<< orphan*/  rmnet_vnd_get_mux (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 

__attribute__((used)) static void rmnet_dellink(struct net_device *dev, struct list_head *head)
{
	struct rmnet_priv *priv = netdev_priv(dev);
	struct net_device *real_dev;
	struct rmnet_endpoint *ep;
	struct rmnet_port *port;
	u8 mux_id;

	real_dev = priv->real_dev;

	if (!real_dev || !rmnet_is_real_dev_registered(real_dev))
		return;

	port = rmnet_get_port_rtnl(real_dev);

	mux_id = rmnet_vnd_get_mux(dev);

	ep = rmnet_get_endpoint(port, mux_id);
	if (ep) {
		hlist_del_init_rcu(&ep->hlnode);
		rmnet_unregister_bridge(dev, port);
		rmnet_vnd_dellink(mux_id, port, ep);
		kfree(ep);
	}
	rmnet_unregister_real_device(real_dev, port);

	unregister_netdevice_queue(dev, head);
}