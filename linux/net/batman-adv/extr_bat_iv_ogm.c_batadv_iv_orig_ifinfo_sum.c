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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  ogm_cnt_lock; } ;
struct batadv_orig_node {TYPE_2__ bat_iv; } ;
struct TYPE_3__ {int /*<<< orphan*/  bcast_own_sum; } ;
struct batadv_orig_ifinfo {TYPE_1__ bat_iv; } ;
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 struct batadv_orig_ifinfo* batadv_orig_ifinfo_get (struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_orig_ifinfo_put (struct batadv_orig_ifinfo*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 batadv_iv_orig_ifinfo_sum(struct batadv_orig_node *orig_node,
				    struct batadv_hard_iface *if_outgoing)
{
	struct batadv_orig_ifinfo *orig_ifinfo;
	u8 sum;

	orig_ifinfo = batadv_orig_ifinfo_get(orig_node, if_outgoing);
	if (!orig_ifinfo)
		return 0;

	spin_lock_bh(&orig_node->bat_iv.ogm_cnt_lock);
	sum = orig_ifinfo->bat_iv.bcast_own_sum;
	spin_unlock_bh(&orig_node->bat_iv.ogm_cnt_lock);

	batadv_orig_ifinfo_put(orig_ifinfo);

	return sum;
}