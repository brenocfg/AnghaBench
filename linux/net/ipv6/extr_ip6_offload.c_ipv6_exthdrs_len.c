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
struct net_offload {int flags; } ;
struct ipv6hdr {int nexthdr; } ;
struct ipv6_opt_hdr {int nexthdr; } ;

/* Variables and functions */
 int INET6_PROTO_GSO_EXTHDR ; 
 int NEXTHDR_HOP ; 
 int /*<<< orphan*/ * inet6_offloads ; 
 int ipv6_optlen (struct ipv6_opt_hdr*) ; 
 struct net_offload* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipv6_exthdrs_len(struct ipv6hdr *iph,
			    const struct net_offload **opps)
{
	struct ipv6_opt_hdr *opth = (void *)iph;
	int len = 0, proto, optlen = sizeof(*iph);

	proto = iph->nexthdr;
	for (;;) {
		if (proto != NEXTHDR_HOP) {
			*opps = rcu_dereference(inet6_offloads[proto]);
			if (unlikely(!(*opps)))
				break;
			if (!((*opps)->flags & INET6_PROTO_GSO_EXTHDR))
				break;
		}
		opth = (void *)opth + optlen;
		optlen = ipv6_optlen(opth);
		len += optlen;
		proto = opth->nexthdr;
	}
	return len;
}