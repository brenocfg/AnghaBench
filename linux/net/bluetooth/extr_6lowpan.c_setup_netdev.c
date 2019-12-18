#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  state; int /*<<< orphan*/  ifindex; int /*<<< orphan*/ * netdev_ops; scalar_t__ dev_addr; int /*<<< orphan*/  addr_assign_type; } ;
struct lowpan_btle_dev {int /*<<< orphan*/  list; int /*<<< orphan*/  peers; TYPE_1__* hdev; struct net_device* netdev; } ;
struct l2cap_chan {int /*<<< orphan*/  src_type; int /*<<< orphan*/  src; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; TYPE_3__* conn; } ;
struct TYPE_6__ {TYPE_2__* hcon; } ;
struct TYPE_5__ {TYPE_1__* hdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_INFO (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFACE_NAME_TEMPLATE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOWPAN_LLTYPE_BTLE ; 
 int /*<<< orphan*/  LOWPAN_PRIV_SIZE (int) ; 
 int /*<<< orphan*/  NET_ADDR_PERM ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __LINK_STATE_PRESENT ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  baswap (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_6lowpan_devices ; 
 int /*<<< orphan*/  bt_type ; 
 int /*<<< orphan*/  devices_lock ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct lowpan_btle_dev* lowpan_btle_dev (struct net_device*) ; 
 int lowpan_register_netdev (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_ops ; 
 int /*<<< orphan*/  netdev_setup ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_netdev(struct l2cap_chan *chan, struct lowpan_btle_dev **dev)
{
	struct net_device *netdev;
	int err = 0;

	netdev = alloc_netdev(LOWPAN_PRIV_SIZE(sizeof(struct lowpan_btle_dev)),
			      IFACE_NAME_TEMPLATE, NET_NAME_UNKNOWN,
			      netdev_setup);
	if (!netdev)
		return -ENOMEM;

	netdev->addr_assign_type = NET_ADDR_PERM;
	baswap((void *)netdev->dev_addr, &chan->src);

	netdev->netdev_ops = &netdev_ops;
	SET_NETDEV_DEV(netdev, &chan->conn->hcon->hdev->dev);
	SET_NETDEV_DEVTYPE(netdev, &bt_type);

	*dev = lowpan_btle_dev(netdev);
	(*dev)->netdev = netdev;
	(*dev)->hdev = chan->conn->hcon->hdev;
	INIT_LIST_HEAD(&(*dev)->peers);

	spin_lock(&devices_lock);
	INIT_LIST_HEAD(&(*dev)->list);
	list_add_rcu(&(*dev)->list, &bt_6lowpan_devices);
	spin_unlock(&devices_lock);

	err = lowpan_register_netdev(netdev, LOWPAN_LLTYPE_BTLE);
	if (err < 0) {
		BT_INFO("register_netdev failed %d", err);
		spin_lock(&devices_lock);
		list_del_rcu(&(*dev)->list);
		spin_unlock(&devices_lock);
		free_netdev(netdev);
		goto out;
	}

	BT_DBG("ifindex %d peer bdaddr %pMR type %d my addr %pMR type %d",
	       netdev->ifindex, &chan->dst, chan->dst_type,
	       &chan->src, chan->src_type);
	set_bit(__LINK_STATE_PRESENT, &netdev->state);

	return 0;

out:
	return err;
}