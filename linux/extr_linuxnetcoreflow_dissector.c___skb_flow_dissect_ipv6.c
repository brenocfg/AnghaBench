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
struct ipv6hdr {int /*<<< orphan*/  hop_limit; } ;
struct flow_dissector_key_ip {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct flow_dissector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IP ; 
 int /*<<< orphan*/  dissector_uses_key (struct flow_dissector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (struct ipv6hdr const*) ; 
 struct flow_dissector_key_ip* skb_flow_dissector_target (struct flow_dissector*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
__skb_flow_dissect_ipv6(const struct sk_buff *skb,
			struct flow_dissector *flow_dissector,
			void *target_container, void *data, const struct ipv6hdr *iph)
{
	struct flow_dissector_key_ip *key_ip;

	if (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_IP))
		return;

	key_ip = skb_flow_dissector_target(flow_dissector,
					   FLOW_DISSECTOR_KEY_IP,
					   target_container);
	key_ip->tos = ipv6_get_dsfield(iph);
	key_ip->ttl = iph->hop_limit;
}