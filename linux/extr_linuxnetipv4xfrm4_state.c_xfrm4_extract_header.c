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
struct iphdr {int ihl; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int ihl; int optlen; int /*<<< orphan*/  flow_lbl; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 TYPE_1__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int xfrm4_extract_header(struct sk_buff *skb)
{
	const struct iphdr *iph = ip_hdr(skb);

	XFRM_MODE_SKB_CB(skb)->ihl = sizeof(*iph);
	XFRM_MODE_SKB_CB(skb)->id = iph->id;
	XFRM_MODE_SKB_CB(skb)->frag_off = iph->frag_off;
	XFRM_MODE_SKB_CB(skb)->tos = iph->tos;
	XFRM_MODE_SKB_CB(skb)->ttl = iph->ttl;
	XFRM_MODE_SKB_CB(skb)->optlen = iph->ihl * 4 - sizeof(*iph);
	memset(XFRM_MODE_SKB_CB(skb)->flow_lbl, 0,
	       sizeof(XFRM_MODE_SKB_CB(skb)->flow_lbl));

	return 0;
}