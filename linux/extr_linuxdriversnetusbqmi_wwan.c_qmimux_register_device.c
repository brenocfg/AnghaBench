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
struct qmimux_priv {struct net_device* real_dev; int /*<<< orphan*/  mux_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct qmimux_priv* netdev_priv (struct net_device*) ; 
 int netdev_upper_dev_link (struct net_device*,struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stacked_transfer_operstate (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  qmimux_setup ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int qmimux_register_device(struct net_device *real_dev, u8 mux_id)
{
	struct net_device *new_dev;
	struct qmimux_priv *priv;
	int err;

	new_dev = alloc_netdev(sizeof(struct qmimux_priv),
			       "qmimux%d", NET_NAME_UNKNOWN, qmimux_setup);
	if (!new_dev)
		return -ENOBUFS;

	dev_net_set(new_dev, dev_net(real_dev));
	priv = netdev_priv(new_dev);
	priv->mux_id = mux_id;
	priv->real_dev = real_dev;

	err = register_netdevice(new_dev);
	if (err < 0)
		goto out_free_newdev;

	/* Account for reference in struct qmimux_priv_priv */
	dev_hold(real_dev);

	err = netdev_upper_dev_link(real_dev, new_dev, NULL);
	if (err)
		goto out_unregister_netdev;

	netif_stacked_transfer_operstate(real_dev, new_dev);

	return 0;

out_unregister_netdev:
	unregister_netdevice(new_dev);
	dev_put(real_dev);

out_free_newdev:
	free_netdev(new_dev);
	return err;
}