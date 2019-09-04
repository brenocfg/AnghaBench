#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; TYPE_2__* ieee802154_ptr; int /*<<< orphan*/  type; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; scalar_t__ needed_headroom; } ;
struct TYPE_6__ {TYPE_4__* wpan_phy; } ;
struct ieee802154_sub_if_data {int /*<<< orphan*/  list; struct ieee802154_local* local; TYPE_2__ wpan_dev; struct net_device* dev; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_4__* phy; scalar_t__ extra_tx_headroom; } ;
struct ieee802154_local {int /*<<< orphan*/  iflist_mtx; int /*<<< orphan*/  interfaces; TYPE_3__ hw; TYPE_1__* phy; } ;
typedef  enum nl802154_iftype { ____Placeholder_nl802154_iftype } nl802154_iftype ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_8__ {int /*<<< orphan*/  perm_extended_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE802154 ; 
 int /*<<< orphan*/  ARPHRD_IEEE802154_MONITOR ; 
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct net_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  IEEE802154_EXTENDED_ADDR_LEN ; 
 scalar_t__ IEEE802154_MAX_HEADER_LEN ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
#define  NL802154_IFTYPE_MONITOR 129 
#define  NL802154_IFTYPE_NODE 128 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_netdev (int,char const*,unsigned char,int /*<<< orphan*/ ) ; 
 int dev_alloc_name (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ieee802154_if_setup ; 
 int /*<<< orphan*/  ieee802154_is_valid_extended_unicast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_le64_to_be64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ieee802154_setup_sdata (struct ieee802154_sub_if_data*,int) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee802154_sub_if_data* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  wpan_phy_net (TYPE_4__*) ; 

struct net_device *
ieee802154_if_add(struct ieee802154_local *local, const char *name,
		  unsigned char name_assign_type, enum nl802154_iftype type,
		  __le64 extended_addr)
{
	struct net_device *ndev = NULL;
	struct ieee802154_sub_if_data *sdata = NULL;
	int ret = -ENOMEM;

	ASSERT_RTNL();

	ndev = alloc_netdev(sizeof(*sdata), name,
			    name_assign_type, ieee802154_if_setup);
	if (!ndev)
		return ERR_PTR(-ENOMEM);

	ndev->needed_headroom = local->hw.extra_tx_headroom +
				IEEE802154_MAX_HEADER_LEN;

	ret = dev_alloc_name(ndev, ndev->name);
	if (ret < 0)
		goto err;

	ieee802154_le64_to_be64(ndev->perm_addr,
				&local->hw.phy->perm_extended_addr);
	switch (type) {
	case NL802154_IFTYPE_NODE:
		ndev->type = ARPHRD_IEEE802154;
		if (ieee802154_is_valid_extended_unicast_addr(extended_addr))
			ieee802154_le64_to_be64(ndev->dev_addr, &extended_addr);
		else
			memcpy(ndev->dev_addr, ndev->perm_addr,
			       IEEE802154_EXTENDED_ADDR_LEN);
		break;
	case NL802154_IFTYPE_MONITOR:
		ndev->type = ARPHRD_IEEE802154_MONITOR;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	/* TODO check this */
	SET_NETDEV_DEV(ndev, &local->phy->dev);
	dev_net_set(ndev, wpan_phy_net(local->hw.phy));
	sdata = netdev_priv(ndev);
	ndev->ieee802154_ptr = &sdata->wpan_dev;
	memcpy(sdata->name, ndev->name, IFNAMSIZ);
	sdata->dev = ndev;
	sdata->wpan_dev.wpan_phy = local->hw.phy;
	sdata->local = local;

	/* setup type-dependent data */
	ret = ieee802154_setup_sdata(sdata, type);
	if (ret)
		goto err;

	ret = register_netdevice(ndev);
	if (ret < 0)
		goto err;

	mutex_lock(&local->iflist_mtx);
	list_add_tail_rcu(&sdata->list, &local->interfaces);
	mutex_unlock(&local->iflist_mtx);

	return ndev;

err:
	free_netdev(ndev);
	return ERR_PTR(ret);
}