#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ icmp; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_3__ src; } ;
struct icmp6hdr {scalar_t__ icmp6_type; int /*<<< orphan*/  icmp6_identifier; int /*<<< orphan*/  icmp6_cksum; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 scalar_t__ ICMPV6_ECHO_REPLY ; 
 scalar_t__ ICMPV6_ECHO_REQUEST ; 
 int /*<<< orphan*/  inet_proto_csum_replace2 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_csum_update (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,struct nf_conntrack_tuple const*,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool
icmpv6_manip_pkt(struct sk_buff *skb,
		 unsigned int iphdroff, unsigned int hdroff,
		 const struct nf_conntrack_tuple *tuple,
		 enum nf_nat_manip_type maniptype)
{
	struct icmp6hdr *hdr;

	if (skb_ensure_writable(skb, hdroff + sizeof(*hdr)))
		return false;

	hdr = (struct icmp6hdr *)(skb->data + hdroff);
	nf_csum_update(skb, iphdroff, &hdr->icmp6_cksum, tuple, maniptype);
	if (hdr->icmp6_type == ICMPV6_ECHO_REQUEST ||
	    hdr->icmp6_type == ICMPV6_ECHO_REPLY) {
		inet_proto_csum_replace2(&hdr->icmp6_cksum, skb,
					 hdr->icmp6_identifier,
					 tuple->src.u.icmp.id, false);
		hdr->icmp6_identifier = tuple->src.u.icmp.id;
	}
	return true;
}