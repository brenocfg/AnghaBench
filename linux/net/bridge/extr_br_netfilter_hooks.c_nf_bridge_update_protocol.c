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
struct nf_bridge_info {int orig_proto; } ;

/* Variables and functions */
#define  BRNF_PROTO_8021Q 130 
#define  BRNF_PROTO_PPPOE 129 
#define  BRNF_PROTO_UNCHANGED 128 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_PPP_SES ; 
 void* htons (int /*<<< orphan*/ ) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 

void nf_bridge_update_protocol(struct sk_buff *skb)
{
	const struct nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	switch (nf_bridge->orig_proto) {
	case BRNF_PROTO_8021Q:
		skb->protocol = htons(ETH_P_8021Q);
		break;
	case BRNF_PROTO_PPPOE:
		skb->protocol = htons(ETH_P_PPP_SES);
		break;
	case BRNF_PROTO_UNCHANGED:
		break;
	}
}