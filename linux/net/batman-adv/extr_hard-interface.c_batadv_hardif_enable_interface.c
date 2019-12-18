#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;
struct batadv_priv {TYPE_2__* algo_ops; int /*<<< orphan*/  fragmentation; } ;
struct TYPE_10__ {TYPE_3__* dev; int /*<<< orphan*/  func; int /*<<< orphan*/  type; } ;
struct batadv_hard_iface {scalar_t__ if_status; struct net_device* soft_iface; TYPE_3__* net_dev; TYPE_6__ batman_adv_ptype; int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_9__ {scalar_t__ mtu; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int (* enable ) (struct batadv_hard_iface*) ;int /*<<< orphan*/  (* enabled ) (struct batadv_hard_iface*) ;} ;
struct TYPE_8__ {TYPE_1__ iface; } ;

/* Variables and functions */
 scalar_t__ BATADV_IF_INACTIVE ; 
 scalar_t__ BATADV_IF_NOT_IN_USE ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  ETH_P_BATMAN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_batman_skb_recv ; 
 int /*<<< orphan*/  batadv_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_hardif_activate_interface (struct batadv_hard_iface*) ; 
 scalar_t__ batadv_hardif_is_iface_up (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hardif_recalc_extra_skbroom (struct net_device*) ; 
 int /*<<< orphan*/  batadv_info (struct net_device*,char*,int /*<<< orphan*/ ,...) ; 
 int batadv_master_del_slave (struct batadv_hard_iface*,struct net_device*) ; 
 int batadv_max_header_len () ; 
 struct net_device* batadv_softif_create (struct net*,char const*) ; 
 int /*<<< orphan*/  batadv_softif_is_valid (struct net_device*) ; 
 int /*<<< orphan*/  dev_add_pack (TYPE_6__*) ; 
 struct net_device* dev_get_by_name (struct net*,char const*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct net_device* netdev_master_upper_dev_get (TYPE_3__*) ; 
 int netdev_master_upper_dev_link (TYPE_3__*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (TYPE_3__*,struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  stub2 (struct batadv_hard_iface*) ; 

int batadv_hardif_enable_interface(struct batadv_hard_iface *hard_iface,
				   struct net *net, const char *iface_name)
{
	struct batadv_priv *bat_priv;
	struct net_device *soft_iface, *master;
	__be16 ethertype = htons(ETH_P_BATMAN);
	int max_header_len = batadv_max_header_len();
	int ret;

	if (hard_iface->if_status != BATADV_IF_NOT_IN_USE)
		goto out;

	kref_get(&hard_iface->refcount);

	soft_iface = dev_get_by_name(net, iface_name);

	if (!soft_iface) {
		soft_iface = batadv_softif_create(net, iface_name);

		if (!soft_iface) {
			ret = -ENOMEM;
			goto err;
		}

		/* dev_get_by_name() increases the reference counter for us */
		dev_hold(soft_iface);
	}

	if (!batadv_softif_is_valid(soft_iface)) {
		pr_err("Can't create batman mesh interface %s: already exists as regular interface\n",
		       soft_iface->name);
		ret = -EINVAL;
		goto err_dev;
	}

	/* check if the interface is enslaved in another virtual one and
	 * in that case unlink it first
	 */
	master = netdev_master_upper_dev_get(hard_iface->net_dev);
	ret = batadv_master_del_slave(hard_iface, master);
	if (ret)
		goto err_dev;

	hard_iface->soft_iface = soft_iface;
	bat_priv = netdev_priv(hard_iface->soft_iface);

	ret = netdev_master_upper_dev_link(hard_iface->net_dev,
					   soft_iface, NULL, NULL, NULL);
	if (ret)
		goto err_dev;

	ret = bat_priv->algo_ops->iface.enable(hard_iface);
	if (ret < 0)
		goto err_upper;

	hard_iface->if_status = BATADV_IF_INACTIVE;

	kref_get(&hard_iface->refcount);
	hard_iface->batman_adv_ptype.type = ethertype;
	hard_iface->batman_adv_ptype.func = batadv_batman_skb_recv;
	hard_iface->batman_adv_ptype.dev = hard_iface->net_dev;
	dev_add_pack(&hard_iface->batman_adv_ptype);

	batadv_info(hard_iface->soft_iface, "Adding interface: %s\n",
		    hard_iface->net_dev->name);

	if (atomic_read(&bat_priv->fragmentation) &&
	    hard_iface->net_dev->mtu < ETH_DATA_LEN + max_header_len)
		batadv_info(hard_iface->soft_iface,
			    "The MTU of interface %s is too small (%i) to handle the transport of batman-adv packets. Packets going over this interface will be fragmented on layer2 which could impact the performance. Setting the MTU to %i would solve the problem.\n",
			    hard_iface->net_dev->name, hard_iface->net_dev->mtu,
			    ETH_DATA_LEN + max_header_len);

	if (!atomic_read(&bat_priv->fragmentation) &&
	    hard_iface->net_dev->mtu < ETH_DATA_LEN + max_header_len)
		batadv_info(hard_iface->soft_iface,
			    "The MTU of interface %s is too small (%i) to handle the transport of batman-adv packets. If you experience problems getting traffic through try increasing the MTU to %i.\n",
			    hard_iface->net_dev->name, hard_iface->net_dev->mtu,
			    ETH_DATA_LEN + max_header_len);

	if (batadv_hardif_is_iface_up(hard_iface))
		batadv_hardif_activate_interface(hard_iface);
	else
		batadv_err(hard_iface->soft_iface,
			   "Not using interface %s (retrying later): interface not active\n",
			   hard_iface->net_dev->name);

	batadv_hardif_recalc_extra_skbroom(soft_iface);

	if (bat_priv->algo_ops->iface.enabled)
		bat_priv->algo_ops->iface.enabled(hard_iface);

out:
	return 0;

err_upper:
	netdev_upper_dev_unlink(hard_iface->net_dev, soft_iface);
err_dev:
	hard_iface->soft_iface = NULL;
	dev_put(soft_iface);
err:
	batadv_hardif_put(hard_iface);
	return ret;
}