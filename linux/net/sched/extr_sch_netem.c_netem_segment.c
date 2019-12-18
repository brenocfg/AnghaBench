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
struct sk_buff {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct sk_buff*) ; 
 int NETIF_F_GSO_MASK ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int netif_skb_features (struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *netem_segment(struct sk_buff *skb, struct Qdisc *sch,
				     struct sk_buff **to_free)
{
	struct sk_buff *segs;
	netdev_features_t features = netif_skb_features(skb);

	segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);

	if (IS_ERR_OR_NULL(segs)) {
		qdisc_drop(skb, sch, to_free);
		return NULL;
	}
	consume_skb(skb);
	return segs;
}