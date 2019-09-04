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
struct TYPE_2__ {int /*<<< orphan*/  ogm_cnt_lock; int /*<<< orphan*/ * bcast_own_sum; int /*<<< orphan*/ * bcast_own; } ;
struct batadv_orig_node {TYPE_1__ bat_iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_iv_ogm_drop_bcast_own_entry (struct batadv_orig_node*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  batadv_iv_ogm_drop_bcast_own_sum_entry (struct batadv_orig_node*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int batadv_iv_ogm_orig_del_if(struct batadv_orig_node *orig_node,
				     unsigned int max_if_num,
				     unsigned int del_if_num)
{
	spin_lock_bh(&orig_node->bat_iv.ogm_cnt_lock);

	if (max_if_num == 0) {
		kfree(orig_node->bat_iv.bcast_own);
		kfree(orig_node->bat_iv.bcast_own_sum);
		orig_node->bat_iv.bcast_own = NULL;
		orig_node->bat_iv.bcast_own_sum = NULL;
	} else {
		batadv_iv_ogm_drop_bcast_own_entry(orig_node, max_if_num,
						   del_if_num);
		batadv_iv_ogm_drop_bcast_own_sum_entry(orig_node, max_if_num,
						       del_if_num);
	}

	spin_unlock_bh(&orig_node->bat_iv.ogm_cnt_lock);

	return 0;
}