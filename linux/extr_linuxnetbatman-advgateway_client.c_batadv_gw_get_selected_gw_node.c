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
struct TYPE_2__ {int /*<<< orphan*/  curr_gw; } ;
struct batadv_priv {TYPE_1__ gw; } ;
struct batadv_gw_node {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 struct batadv_gw_node* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct batadv_gw_node *
batadv_gw_get_selected_gw_node(struct batadv_priv *bat_priv)
{
	struct batadv_gw_node *gw_node;

	rcu_read_lock();
	gw_node = rcu_dereference(bat_priv->gw.curr_gw);
	if (!gw_node)
		goto out;

	if (!kref_get_unless_zero(&gw_node->refcount))
		gw_node = NULL;

out:
	rcu_read_unlock();
	return gw_node;
}