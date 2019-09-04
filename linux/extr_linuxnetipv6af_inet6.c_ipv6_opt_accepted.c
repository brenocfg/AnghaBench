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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_3__ {scalar_t__ odstopts; scalar_t__ dstopts; scalar_t__ osrcrt; scalar_t__ srcrt; scalar_t__ rxflow; scalar_t__ ohopopts; scalar_t__ hopopts; } ;
struct TYPE_4__ {TYPE_1__ bits; scalar_t__ all; } ;
struct ipv6_pinfo {TYPE_2__ rxopt; } ;
struct inet6_skb_parm {int flags; scalar_t__ dst0; scalar_t__ dst1; scalar_t__ srcrt; } ;

/* Variables and functions */
 int IP6SKB_HOPBYHOP ; 
 struct ipv6_pinfo* inet6_sk (struct sock const*) ; 
 scalar_t__ ip6_flowinfo (struct ipv6hdr*) ; 
 scalar_t__ skb_network_header (struct sk_buff const*) ; 

bool ipv6_opt_accepted(const struct sock *sk, const struct sk_buff *skb,
		       const struct inet6_skb_parm *opt)
{
	const struct ipv6_pinfo *np = inet6_sk(sk);

	if (np->rxopt.all) {
		if (((opt->flags & IP6SKB_HOPBYHOP) &&
		     (np->rxopt.bits.hopopts || np->rxopt.bits.ohopopts)) ||
		    (ip6_flowinfo((struct ipv6hdr *) skb_network_header(skb)) &&
		     np->rxopt.bits.rxflow) ||
		    (opt->srcrt && (np->rxopt.bits.srcrt ||
		     np->rxopt.bits.osrcrt)) ||
		    ((opt->dst1 || opt->dst0) &&
		     (np->rxopt.bits.dstopts || np->rxopt.bits.odstopts)))
			return true;
	}
	return false;
}