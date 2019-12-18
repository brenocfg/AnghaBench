#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct batadv_priv {TYPE_2__* algo_ops; } ;
struct batadv_hard_iface {int /*<<< orphan*/  num_bcasts; int /*<<< orphan*/  wifi_flags; int /*<<< orphan*/  soft_iface; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  if_status; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_mac ) (struct batadv_hard_iface*) ;} ;
struct TYPE_4__ {TYPE_1__ iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_IF_NOT_IN_USE ; 
 int /*<<< orphan*/  BATADV_NUM_BCASTS_WIRELESS ; 
#define  NETDEV_CHANGEADDR 136 
#define  NETDEV_CHANGEMTU 135 
#define  NETDEV_CHANGENAME 134 
#define  NETDEV_CHANGEUPPER 133 
#define  NETDEV_DOWN 132 
#define  NETDEV_GOING_DOWN 131 
 unsigned long NETDEV_POST_TYPE_CHANGE ; 
#define  NETDEV_PRE_TYPE_CHANGE 130 
 unsigned long NETDEV_REGISTER ; 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  batadv_check_known_mac_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_debugfs_rename_hardif (struct batadv_hard_iface*) ; 
 int batadv_hard_if_event_softif (unsigned long,struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_activate_interface (struct batadv_hard_iface*) ; 
 struct batadv_hard_iface* batadv_hardif_add_interface (struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_deactivate_interface (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hardif_generation ; 
 struct batadv_hard_iface* batadv_hardif_get_by_netdev (struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hardif_remove_interface (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_is_wifi_hardif (struct batadv_hard_iface*) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_primary_if_update_addr (struct batadv_priv*,int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_softif_is_valid (struct net_device*) ; 
 int /*<<< orphan*/  batadv_update_min_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_wifi_flags_evaluate (struct net_device*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct batadv_hard_iface*) ; 

__attribute__((used)) static int batadv_hard_if_event(struct notifier_block *this,
				unsigned long event, void *ptr)
{
	struct net_device *net_dev = netdev_notifier_info_to_dev(ptr);
	struct batadv_hard_iface *hard_iface;
	struct batadv_hard_iface *primary_if = NULL;
	struct batadv_priv *bat_priv;

	if (batadv_softif_is_valid(net_dev))
		return batadv_hard_if_event_softif(event, net_dev);

	hard_iface = batadv_hardif_get_by_netdev(net_dev);
	if (!hard_iface && (event == NETDEV_REGISTER ||
			    event == NETDEV_POST_TYPE_CHANGE))
		hard_iface = batadv_hardif_add_interface(net_dev);

	if (!hard_iface)
		goto out;

	switch (event) {
	case NETDEV_UP:
		batadv_hardif_activate_interface(hard_iface);
		break;
	case NETDEV_GOING_DOWN:
	case NETDEV_DOWN:
		batadv_hardif_deactivate_interface(hard_iface);
		break;
	case NETDEV_UNREGISTER:
	case NETDEV_PRE_TYPE_CHANGE:
		list_del_rcu(&hard_iface->list);
		batadv_hardif_generation++;

		batadv_hardif_remove_interface(hard_iface);
		break;
	case NETDEV_CHANGEMTU:
		if (hard_iface->soft_iface)
			batadv_update_min_mtu(hard_iface->soft_iface);
		break;
	case NETDEV_CHANGEADDR:
		if (hard_iface->if_status == BATADV_IF_NOT_IN_USE)
			goto hardif_put;

		batadv_check_known_mac_addr(hard_iface->net_dev);

		bat_priv = netdev_priv(hard_iface->soft_iface);
		bat_priv->algo_ops->iface.update_mac(hard_iface);

		primary_if = batadv_primary_if_get_selected(bat_priv);
		if (!primary_if)
			goto hardif_put;

		if (hard_iface == primary_if)
			batadv_primary_if_update_addr(bat_priv, NULL);
		break;
	case NETDEV_CHANGEUPPER:
		hard_iface->wifi_flags = batadv_wifi_flags_evaluate(net_dev);
		if (batadv_is_wifi_hardif(hard_iface))
			hard_iface->num_bcasts = BATADV_NUM_BCASTS_WIRELESS;
		break;
	case NETDEV_CHANGENAME:
		batadv_debugfs_rename_hardif(hard_iface);
		break;
	default:
		break;
	}

hardif_put:
	batadv_hardif_put(hard_iface);
out:
	if (primary_if)
		batadv_hardif_put(primary_if);
	return NOTIFY_DONE;
}