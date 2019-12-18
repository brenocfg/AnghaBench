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
struct batadv_priv {TYPE_2__* algo_ops; } ;
struct batadv_hard_iface {scalar_t__ if_status; int /*<<< orphan*/ * soft_iface; TYPE_3__* net_dev; int /*<<< orphan*/  batman_adv_ptype; } ;
typedef  enum batadv_hard_if_cleanup { ____Placeholder_batadv_hard_if_cleanup } batadv_hard_if_cleanup ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (struct batadv_hard_iface*) ;} ;
struct TYPE_5__ {TYPE_1__ iface; } ;

/* Variables and functions */
 int BATADV_IF_CLEANUP_AUTO ; 
 scalar_t__ BATADV_IF_INACTIVE ; 
 scalar_t__ BATADV_IF_NOT_IN_USE ; 
 int /*<<< orphan*/  batadv_gw_check_client_stop (struct batadv_priv*) ; 
 int batadv_hardif_cnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_hardif_deactivate_interface (struct batadv_hard_iface*) ; 
 struct batadv_hard_iface* batadv_hardif_get_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hardif_recalc_extra_skbroom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_primary_if_select (struct batadv_priv*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_purge_orig_ref (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_purge_outstanding_packets (struct batadv_priv*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_softif_destroy_sysfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_remove_pack (int /*<<< orphan*/ *) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct batadv_hard_iface*) ; 

void batadv_hardif_disable_interface(struct batadv_hard_iface *hard_iface,
				     enum batadv_hard_if_cleanup autodel)
{
	struct batadv_priv *bat_priv = netdev_priv(hard_iface->soft_iface);
	struct batadv_hard_iface *primary_if = NULL;

	batadv_hardif_deactivate_interface(hard_iface);

	if (hard_iface->if_status != BATADV_IF_INACTIVE)
		goto out;

	batadv_info(hard_iface->soft_iface, "Removing interface: %s\n",
		    hard_iface->net_dev->name);
	dev_remove_pack(&hard_iface->batman_adv_ptype);
	batadv_hardif_put(hard_iface);

	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (hard_iface == primary_if) {
		struct batadv_hard_iface *new_if;

		new_if = batadv_hardif_get_active(hard_iface->soft_iface);
		batadv_primary_if_select(bat_priv, new_if);

		if (new_if)
			batadv_hardif_put(new_if);
	}

	bat_priv->algo_ops->iface.disable(hard_iface);
	hard_iface->if_status = BATADV_IF_NOT_IN_USE;

	/* delete all references to this hard_iface */
	batadv_purge_orig_ref(bat_priv);
	batadv_purge_outstanding_packets(bat_priv, hard_iface);
	dev_put(hard_iface->soft_iface);

	netdev_upper_dev_unlink(hard_iface->net_dev, hard_iface->soft_iface);
	batadv_hardif_recalc_extra_skbroom(hard_iface->soft_iface);

	/* nobody uses this interface anymore */
	if (batadv_hardif_cnt(hard_iface->soft_iface) <= 1) {
		batadv_gw_check_client_stop(bat_priv);

		if (autodel == BATADV_IF_CLEANUP_AUTO)
			batadv_softif_destroy_sysfs(hard_iface->soft_iface);
	}

	hard_iface->soft_iface = NULL;
	batadv_hardif_put(hard_iface);

out:
	if (primary_if)
		batadv_hardif_put(primary_if);
}