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
typedef  int u8 ;
struct hlist_node {int dummy; } ;
struct hlist_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  want_lists_lock; int /*<<< orphan*/  num_want_all_rtr6; struct hlist_head want_all_rtr6_list; } ;
struct batadv_priv {TYPE_1__ mcast; } ;
struct batadv_orig_node {int mcast_flags; int /*<<< orphan*/  mcast_handler_lock; struct hlist_node mcast_want_all_rtr6_node; } ;

/* Variables and functions */
 int BATADV_MCAST_WANT_NO_RTR6 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (struct hlist_node*,struct hlist_head*) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (struct hlist_node*) ; 
 int hlist_unhashed (struct hlist_node*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_mcast_want_rtr6_update(struct batadv_priv *bat_priv,
					  struct batadv_orig_node *orig,
					  u8 mcast_flags)
{
	struct hlist_node *node = &orig->mcast_want_all_rtr6_node;
	struct hlist_head *head = &bat_priv->mcast.want_all_rtr6_list;

	lockdep_assert_held(&orig->mcast_handler_lock);

	/* switched from flag set to unset */
	if (!(mcast_flags & BATADV_MCAST_WANT_NO_RTR6) &&
	    orig->mcast_flags & BATADV_MCAST_WANT_NO_RTR6) {
		atomic_inc(&bat_priv->mcast.num_want_all_rtr6);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(!hlist_unhashed(node));

		hlist_add_head_rcu(node, head);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	/* switched from flag unset to set */
	} else if (mcast_flags & BATADV_MCAST_WANT_NO_RTR6 &&
		   !(orig->mcast_flags & BATADV_MCAST_WANT_NO_RTR6)) {
		atomic_dec(&bat_priv->mcast.num_want_all_rtr6);

		spin_lock_bh(&bat_priv->mcast.want_lists_lock);
		/* flag checks above + mcast_handler_lock prevents this */
		WARN_ON(hlist_unhashed(node));

		hlist_del_init_rcu(node);
		spin_unlock_bh(&bat_priv->mcast.want_lists_lock);
	}
}