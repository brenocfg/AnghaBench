#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int network_header; int mac_header; unsigned int mac_len; scalar_t__ protocol; struct sk_buff* next; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
typedef  scalar_t__ __be16 ;
struct TYPE_3__ {int /*<<< orphan*/  np; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_NSH ; 
 int /*<<< orphan*/  ETH_P_TEB ; 
 scalar_t__ IS_ERR_OR_NULL (struct sk_buff*) ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 unsigned int NSH_BASE_HDR_LEN ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,unsigned int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* nsh_hdr (struct sk_buff*) ; 
 unsigned int nsh_hdr_len (TYPE_1__*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_gso_error_unwind (struct sk_buff*,scalar_t__,unsigned int,int,unsigned int) ; 
 struct sk_buff* skb_mac_gso_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,int) ; 
 scalar_t__ tun_p_to_eth_p (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *nsh_gso_segment(struct sk_buff *skb,
				       netdev_features_t features)
{
	struct sk_buff *segs = ERR_PTR(-EINVAL);
	unsigned int nsh_len, mac_len;
	__be16 proto;
	int nhoff;

	skb_reset_network_header(skb);

	nhoff = skb->network_header - skb->mac_header;
	mac_len = skb->mac_len;

	if (unlikely(!pskb_may_pull(skb, NSH_BASE_HDR_LEN)))
		goto out;
	nsh_len = nsh_hdr_len(nsh_hdr(skb));
	if (nsh_len < NSH_BASE_HDR_LEN)
		goto out;
	if (unlikely(!pskb_may_pull(skb, nsh_len)))
		goto out;

	proto = tun_p_to_eth_p(nsh_hdr(skb)->np);
	if (!proto)
		goto out;

	__skb_pull(skb, nsh_len);

	skb_reset_mac_header(skb);
	skb->mac_len = proto == htons(ETH_P_TEB) ? ETH_HLEN : 0;
	skb->protocol = proto;

	features &= NETIF_F_SG;
	segs = skb_mac_gso_segment(skb, features);
	if (IS_ERR_OR_NULL(segs)) {
		skb_gso_error_unwind(skb, htons(ETH_P_NSH), nsh_len,
				     skb->network_header - nhoff,
				     mac_len);
		goto out;
	}

	for (skb = segs; skb; skb = skb->next) {
		skb->protocol = htons(ETH_P_NSH);
		__skb_push(skb, nsh_len);
		skb_set_mac_header(skb, -nhoff);
		skb->network_header = skb->mac_header + mac_len;
		skb->mac_len = mac_len;
	}

out:
	return segs;
}