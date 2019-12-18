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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {unsigned int aggr_len; int /*<<< orphan*/  aggr_list; int /*<<< orphan*/  aggr_list_lock; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  batadv_v_ogm_aggr_list_free (struct batadv_hard_iface*) ; 
 unsigned int batadv_v_ogm_len (struct sk_buff*) ; 
 int /*<<< orphan*/  batadv_v_ogm_send_to_if (struct sk_buff*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static void batadv_v_ogm_aggr_send(struct batadv_hard_iface *hard_iface)
{
	unsigned int aggr_len = hard_iface->bat_v.aggr_len;
	struct sk_buff *skb_aggr;
	unsigned int ogm_len;
	struct sk_buff *skb;

	lockdep_assert_held(&hard_iface->bat_v.aggr_list_lock);

	if (!aggr_len)
		return;

	skb_aggr = dev_alloc_skb(aggr_len + ETH_HLEN + NET_IP_ALIGN);
	if (!skb_aggr) {
		batadv_v_ogm_aggr_list_free(hard_iface);
		return;
	}

	skb_reserve(skb_aggr, ETH_HLEN + NET_IP_ALIGN);
	skb_reset_network_header(skb_aggr);

	while ((skb = skb_dequeue(&hard_iface->bat_v.aggr_list))) {
		hard_iface->bat_v.aggr_len -= batadv_v_ogm_len(skb);

		ogm_len = batadv_v_ogm_len(skb);
		skb_put_data(skb_aggr, skb->data, ogm_len);

		consume_skb(skb);
	}

	batadv_v_ogm_send_to_if(skb_aggr, hard_iface);
}