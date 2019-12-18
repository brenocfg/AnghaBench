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
struct nf_icmp_net {int /*<<< orphan*/  timeout; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_icmpv6_timeout ; 
 struct nf_icmp_net* nf_icmpv6_pernet (struct net*) ; 

void nf_conntrack_icmpv6_init_net(struct net *net)
{
	struct nf_icmp_net *in = nf_icmpv6_pernet(net);

	in->timeout = nf_ct_icmpv6_timeout;
}