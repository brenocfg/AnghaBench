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
struct iphdr {int ihl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
typedef  struct iphdr u8 ;
struct xfrm_state {struct ah_data* data; } ;
struct sk_buff {int dummy; } ;
struct ip_auth_hdr {struct iphdr* auth_data; } ;
struct crypto_async_request {struct sk_buff* data; } ;
struct ah_data {int icv_trunc_len; int /*<<< orphan*/  ahash; } ;
struct TYPE_4__ {struct iphdr* tmp; } ;
struct TYPE_3__ {struct xfrm_state* xfrm; } ;

/* Variables and functions */
 TYPE_2__* AH_SKB_CB (struct sk_buff*) ; 
 struct iphdr* ah_tmp_icv (int /*<<< orphan*/ ,struct iphdr*,int) ; 
 struct ip_auth_hdr* ip_auth_hdr (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct iphdr*) ; 
 int /*<<< orphan*/  memcpy (struct iphdr*,struct iphdr*,int) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_output_resume (struct sk_buff*,int) ; 

__attribute__((used)) static void ah_output_done(struct crypto_async_request *base, int err)
{
	u8 *icv;
	struct iphdr *iph;
	struct sk_buff *skb = base->data;
	struct xfrm_state *x = skb_dst(skb)->xfrm;
	struct ah_data *ahp = x->data;
	struct iphdr *top_iph = ip_hdr(skb);
	struct ip_auth_hdr *ah = ip_auth_hdr(skb);
	int ihl = ip_hdrlen(skb);

	iph = AH_SKB_CB(skb)->tmp;
	icv = ah_tmp_icv(ahp->ahash, iph, ihl);
	memcpy(ah->auth_data, icv, ahp->icv_trunc_len);

	top_iph->tos = iph->tos;
	top_iph->ttl = iph->ttl;
	top_iph->frag_off = iph->frag_off;
	if (top_iph->ihl != 5) {
		top_iph->daddr = iph->daddr;
		memcpy(top_iph+1, iph+1, top_iph->ihl*4 - sizeof(struct iphdr));
	}

	kfree(AH_SKB_CB(skb)->tmp);
	xfrm_output_resume(skb, err);
}