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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ aggr_len; int /*<<< orphan*/  aggr_list; int /*<<< orphan*/  aggr_list_lock; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_v_ogm_aggr_list_free(struct batadv_hard_iface *hard_iface)
{
	struct sk_buff *skb;

	lockdep_assert_held(&hard_iface->bat_v.aggr_list_lock);

	while ((skb = skb_dequeue(&hard_iface->bat_v.aggr_list)))
		kfree_skb(skb);

	hard_iface->bat_v.aggr_len = 0;
}