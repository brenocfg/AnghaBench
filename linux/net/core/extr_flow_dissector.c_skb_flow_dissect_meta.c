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
struct sk_buff {int /*<<< orphan*/  skb_iif; } ;
struct flow_dissector_key_meta {int /*<<< orphan*/  ingress_ifindex; } ;
struct flow_dissector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_META ; 
 int /*<<< orphan*/  dissector_uses_key (struct flow_dissector*,int /*<<< orphan*/ ) ; 
 struct flow_dissector_key_meta* skb_flow_dissector_target (struct flow_dissector*,int /*<<< orphan*/ ,void*) ; 

void skb_flow_dissect_meta(const struct sk_buff *skb,
			   struct flow_dissector *flow_dissector,
			   void *target_container)
{
	struct flow_dissector_key_meta *meta;

	if (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_META))
		return;

	meta = skb_flow_dissector_target(flow_dissector,
					 FLOW_DISSECTOR_KEY_META,
					 target_container);
	meta->ingress_ifindex = skb->skb_iif;
}