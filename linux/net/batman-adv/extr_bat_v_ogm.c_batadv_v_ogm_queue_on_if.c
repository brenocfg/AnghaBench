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
struct batadv_priv {int /*<<< orphan*/  aggregated_ogms; } ;
struct TYPE_2__ {int /*<<< orphan*/  aggr_list_lock; int /*<<< orphan*/  aggr_list; int /*<<< orphan*/  aggr_len; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_v_ogm_aggr_send (struct batadv_hard_iface*) ; 
 scalar_t__ batadv_v_ogm_len (struct sk_buff*) ; 
 int /*<<< orphan*/  batadv_v_ogm_queue_left (struct sk_buff*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_v_ogm_send_to_if (struct sk_buff*,struct batadv_hard_iface*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_v_ogm_queue_on_if(struct sk_buff *skb,
				     struct batadv_hard_iface *hard_iface)
{
	struct batadv_priv *bat_priv = netdev_priv(hard_iface->soft_iface);

	if (!atomic_read(&bat_priv->aggregated_ogms)) {
		batadv_v_ogm_send_to_if(skb, hard_iface);
		return;
	}

	spin_lock_bh(&hard_iface->bat_v.aggr_list_lock);
	if (!batadv_v_ogm_queue_left(skb, hard_iface))
		batadv_v_ogm_aggr_send(hard_iface);

	hard_iface->bat_v.aggr_len += batadv_v_ogm_len(skb);
	skb_queue_tail(&hard_iface->bat_v.aggr_list, skb);
	spin_unlock_bh(&hard_iface->bat_v.aggr_list_lock);
}