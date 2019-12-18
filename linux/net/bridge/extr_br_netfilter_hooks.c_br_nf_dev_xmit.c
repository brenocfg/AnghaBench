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
struct nf_bridge_info {scalar_t__ bridged_dnat; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_nf_pre_routing_finish_bridge_slow (struct sk_buff*) ; 
 struct nf_bridge_info* nf_bridge_info_get (struct sk_buff*) ; 

__attribute__((used)) static int br_nf_dev_xmit(struct sk_buff *skb)
{
	const struct nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);

	if (nf_bridge && nf_bridge->bridged_dnat) {
		br_nf_pre_routing_finish_bridge_slow(skb);
		return 1;
	}
	return 0;
}