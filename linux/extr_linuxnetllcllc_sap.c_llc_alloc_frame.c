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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  protocol; } ;
struct net_device {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ LLC_PDU_TYPE_U ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ llc_mac_header_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 

struct sk_buff *llc_alloc_frame(struct sock *sk, struct net_device *dev,
				u8 type, u32 data_size)
{
	int hlen = type == LLC_PDU_TYPE_U ? 3 : 4;
	struct sk_buff *skb;

	hlen += llc_mac_header_len(dev->type);
	skb = alloc_skb(hlen + data_size, GFP_ATOMIC);

	if (skb) {
		skb_reset_mac_header(skb);
		skb_reserve(skb, hlen);
		skb_reset_network_header(skb);
		skb_reset_transport_header(skb);
		skb->protocol = htons(ETH_P_802_2);
		skb->dev      = dev;
		if (sk != NULL)
			skb_set_owner_w(skb, sk);
	}
	return skb;
}