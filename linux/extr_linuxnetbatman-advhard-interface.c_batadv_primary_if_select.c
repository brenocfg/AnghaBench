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
struct batadv_priv {TYPE_2__* algo_ops; int /*<<< orphan*/  primary_if; } ;
struct batadv_hard_iface {int /*<<< orphan*/  refcount; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* primary_set ) (struct batadv_hard_iface*) ;} ;
struct TYPE_4__ {TYPE_1__ iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_primary_if_update_addr (struct batadv_priv*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct batadv_hard_iface*) ; 
 struct batadv_hard_iface* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct batadv_hard_iface*) ; 

__attribute__((used)) static void batadv_primary_if_select(struct batadv_priv *bat_priv,
				     struct batadv_hard_iface *new_hard_iface)
{
	struct batadv_hard_iface *curr_hard_iface;

	ASSERT_RTNL();

	if (new_hard_iface)
		kref_get(&new_hard_iface->refcount);

	curr_hard_iface = rcu_dereference_protected(bat_priv->primary_if, 1);
	rcu_assign_pointer(bat_priv->primary_if, new_hard_iface);

	if (!new_hard_iface)
		goto out;

	bat_priv->algo_ops->iface.primary_set(new_hard_iface);
	batadv_primary_if_update_addr(bat_priv, curr_hard_iface);

out:
	if (curr_hard_iface)
		batadv_hardif_put(curr_hard_iface);
}