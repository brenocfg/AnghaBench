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
struct TYPE_2__ {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  curr_gw; } ;
struct batadv_priv {TYPE_1__ gw; } ;
struct batadv_gw_node {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_gw_node_put (struct batadv_gw_node*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct batadv_gw_node*) ; 
 struct batadv_gw_node* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_gw_select(struct batadv_priv *bat_priv,
			     struct batadv_gw_node *new_gw_node)
{
	struct batadv_gw_node *curr_gw_node;

	spin_lock_bh(&bat_priv->gw.list_lock);

	if (new_gw_node)
		kref_get(&new_gw_node->refcount);

	curr_gw_node = rcu_dereference_protected(bat_priv->gw.curr_gw, 1);
	rcu_assign_pointer(bat_priv->gw.curr_gw, new_gw_node);

	if (curr_gw_node)
		batadv_gw_node_put(curr_gw_node);

	spin_unlock_bh(&bat_priv->gw.list_lock);
}