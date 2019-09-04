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
struct batadv_priv {int /*<<< orphan*/  primary_if; } ;
struct batadv_hard_iface {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 struct batadv_hard_iface* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline struct batadv_hard_iface *
batadv_primary_if_get_selected(struct batadv_priv *bat_priv)
{
	struct batadv_hard_iface *hard_iface;

	rcu_read_lock();
	hard_iface = rcu_dereference(bat_priv->primary_if);
	if (!hard_iface)
		goto out;

	if (!kref_get_unless_zero(&hard_iface->refcount))
		hard_iface = NULL;

out:
	rcu_read_unlock();
	return hard_iface;
}