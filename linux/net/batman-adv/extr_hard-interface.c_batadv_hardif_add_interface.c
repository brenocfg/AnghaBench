#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ogm_buff_mutex; } ;
struct batadv_hard_iface {int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; struct net_device* net_dev; int /*<<< orphan*/  num_bcasts; int /*<<< orphan*/  wifi_flags; int /*<<< orphan*/  neigh_list_lock; TYPE_1__ bat_iv; int /*<<< orphan*/  neigh_list; int /*<<< orphan*/  if_status; int /*<<< orphan*/ * soft_iface; int /*<<< orphan*/  hardif_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BATADV_IF_NOT_IN_USE ; 
 int /*<<< orphan*/  BATADV_NUM_BCASTS_DEFAULT ; 
 int /*<<< orphan*/  BATADV_NUM_BCASTS_WIRELESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_check_known_mac_addr (struct net_device*) ; 
 int /*<<< orphan*/  batadv_debugfs_add_hardif (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hardif_generation ; 
 int /*<<< orphan*/  batadv_hardif_list ; 
 int /*<<< orphan*/  batadv_is_valid_iface (struct net_device*) ; 
 scalar_t__ batadv_is_wifi_hardif (struct batadv_hard_iface*) ; 
 int batadv_sysfs_add_hardif (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  batadv_v_hardif_init (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_wifi_flags_evaluate (struct net_device*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_hard_iface* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct batadv_hard_iface *
batadv_hardif_add_interface(struct net_device *net_dev)
{
	struct batadv_hard_iface *hard_iface;
	int ret;

	ASSERT_RTNL();

	if (!batadv_is_valid_iface(net_dev))
		goto out;

	dev_hold(net_dev);

	hard_iface = kzalloc(sizeof(*hard_iface), GFP_ATOMIC);
	if (!hard_iface)
		goto release_dev;

	ret = batadv_sysfs_add_hardif(&hard_iface->hardif_obj, net_dev);
	if (ret)
		goto free_if;

	hard_iface->net_dev = net_dev;
	hard_iface->soft_iface = NULL;
	hard_iface->if_status = BATADV_IF_NOT_IN_USE;

	batadv_debugfs_add_hardif(hard_iface);

	INIT_LIST_HEAD(&hard_iface->list);
	INIT_HLIST_HEAD(&hard_iface->neigh_list);

	mutex_init(&hard_iface->bat_iv.ogm_buff_mutex);
	spin_lock_init(&hard_iface->neigh_list_lock);
	kref_init(&hard_iface->refcount);

	hard_iface->num_bcasts = BATADV_NUM_BCASTS_DEFAULT;
	hard_iface->wifi_flags = batadv_wifi_flags_evaluate(net_dev);
	if (batadv_is_wifi_hardif(hard_iface))
		hard_iface->num_bcasts = BATADV_NUM_BCASTS_WIRELESS;

	batadv_v_hardif_init(hard_iface);

	batadv_check_known_mac_addr(hard_iface->net_dev);
	kref_get(&hard_iface->refcount);
	list_add_tail_rcu(&hard_iface->list, &batadv_hardif_list);
	batadv_hardif_generation++;

	return hard_iface;

free_if:
	kfree(hard_iface);
release_dev:
	dev_put(net_dev);
out:
	return NULL;
}