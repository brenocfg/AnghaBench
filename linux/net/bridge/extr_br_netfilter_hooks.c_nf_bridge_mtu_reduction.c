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
struct nf_bridge_info {scalar_t__ orig_proto; } ;

/* Variables and functions */
 scalar_t__ BRNF_PROTO_PPPOE ; 
 unsigned int PPPOE_SES_HLEN ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff const*) ; 

__attribute__((used)) static unsigned int nf_bridge_mtu_reduction(const struct sk_buff *skb)
{
	const struct nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	if (nf_bridge->orig_proto == BRNF_PROTO_PPPOE)
		return PPPOE_SES_HLEN;
	return 0;
}