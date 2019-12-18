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
struct sk_buff {scalar_t__ len; } ;
struct iphdr {int frag_off; } ;
struct ip_frag_state {int DF; unsigned int hlen; unsigned int ll_rs; unsigned int mtu; unsigned int ptr; int offset; int not_last_frag; scalar_t__ left; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_MF ; 
 int IP_OFFSET ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ntohs (int) ; 

void ip_frag_init(struct sk_buff *skb, unsigned int hlen,
		  unsigned int ll_rs, unsigned int mtu, bool DF,
		  struct ip_frag_state *state)
{
	struct iphdr *iph = ip_hdr(skb);

	state->DF = DF;
	state->hlen = hlen;
	state->ll_rs = ll_rs;
	state->mtu = mtu;

	state->left = skb->len - hlen;	/* Space per frame */
	state->ptr = hlen;		/* Where to start from */

	state->offset = (ntohs(iph->frag_off) & IP_OFFSET) << 3;
	state->not_last_frag = iph->frag_off & htons(IP_MF);
}