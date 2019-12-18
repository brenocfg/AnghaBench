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
struct sk_buff {int /*<<< orphan*/  truesize; scalar_t__ encapsulation; int /*<<< orphan*/  pkt_type; scalar_t__ skb_iif; int /*<<< orphan*/  dev; int /*<<< orphan*/  pfmemalloc; } ;
struct napi_struct {struct sk_buff* skb; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ gso_type; } ;

/* Variables and functions */
 scalar_t__ NET_IP_ALIGN ; 
 scalar_t__ NET_SKB_PAD ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  SKB_TRUESIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_clear_tag (struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_end_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_ext_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void napi_reuse_skb(struct napi_struct *napi, struct sk_buff *skb)
{
	if (unlikely(skb->pfmemalloc)) {
		consume_skb(skb);
		return;
	}
	__skb_pull(skb, skb_headlen(skb));
	/* restore the reserve we had after netdev_alloc_skb_ip_align() */
	skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN - skb_headroom(skb));
	__vlan_hwaccel_clear_tag(skb);
	skb->dev = napi->dev;
	skb->skb_iif = 0;

	/* eth_type_trans() assumes pkt_type is PACKET_HOST */
	skb->pkt_type = PACKET_HOST;

	skb->encapsulation = 0;
	skb_shinfo(skb)->gso_type = 0;
	skb->truesize = SKB_TRUESIZE(skb_end_offset(skb));
	skb_ext_reset(skb);

	napi->skb = skb;
}