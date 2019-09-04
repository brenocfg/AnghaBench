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
struct sk_buff {void* protocol; } ;
struct iphdr {int version; int ihl; int ttl; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; scalar_t__ check; int /*<<< orphan*/  protocol; void* frag_off; scalar_t__ id; scalar_t__ tos; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  IP_DF ; 
 void* htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff const*) ; 
 struct iphdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

struct iphdr *nf_reject_iphdr_put(struct sk_buff *nskb,
				  const struct sk_buff *oldskb,
				  __u8 protocol, int ttl)
{
	struct iphdr *niph, *oiph = ip_hdr(oldskb);

	skb_reset_network_header(nskb);
	niph = skb_put(nskb, sizeof(struct iphdr));
	niph->version	= 4;
	niph->ihl	= sizeof(struct iphdr) / 4;
	niph->tos	= 0;
	niph->id	= 0;
	niph->frag_off	= htons(IP_DF);
	niph->protocol	= protocol;
	niph->check	= 0;
	niph->saddr	= oiph->daddr;
	niph->daddr	= oiph->saddr;
	niph->ttl	= ttl;

	nskb->protocol = htons(ETH_P_IP);

	return niph;
}