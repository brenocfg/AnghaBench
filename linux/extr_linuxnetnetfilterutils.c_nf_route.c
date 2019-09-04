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
struct nf_ipv6_ops {int (* route ) (struct net*,struct dst_entry**,struct flowi*,int) ;} ;
struct net {int dummy; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int nf_ip_route (struct net*,struct dst_entry**,struct flowi*,int) ; 
 int /*<<< orphan*/  nf_ipv6_ops ; 
 struct nf_ipv6_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int stub1 (struct net*,struct dst_entry**,struct flowi*,int) ; 

int nf_route(struct net *net, struct dst_entry **dst, struct flowi *fl,
	     bool strict, unsigned short family)
{
	const struct nf_ipv6_ops *v6ops;
	int ret = 0;

	switch (family) {
	case AF_INET:
		ret = nf_ip_route(net, dst, fl, strict);
		break;
	case AF_INET6:
		v6ops = rcu_dereference(nf_ipv6_ops);
		if (v6ops)
			ret = v6ops->route(net, dst, fl, strict);
		break;
	}

	return ret;
}