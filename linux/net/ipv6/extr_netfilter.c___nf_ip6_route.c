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
struct net {int dummy; } ;
struct ipv6_pinfo {int dummy; } ;
struct TYPE_3__ {int sk_bound_dev_if; } ;
struct inet_sock {struct ipv6_pinfo* pinet6; TYPE_1__ sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip6; } ;
struct flowi {TYPE_2__ u; } ;
struct dst_entry {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct dst_entry* ip6_route_output (struct net*,void const*,int /*<<< orphan*/ *) ; 

int __nf_ip6_route(struct net *net, struct dst_entry **dst,
		   struct flowi *fl, bool strict)
{
	static const struct ipv6_pinfo fake_pinfo;
	static const struct inet_sock fake_sk = {
		/* makes ip6_route_output set RT6_LOOKUP_F_IFACE: */
		.sk.sk_bound_dev_if = 1,
		.pinet6 = (struct ipv6_pinfo *) &fake_pinfo,
	};
	const void *sk = strict ? &fake_sk : NULL;
	struct dst_entry *result;
	int err;

	result = ip6_route_output(net, sk, &fl->u.ip6);
	err = result->error;
	if (err)
		dst_release(result);
	else
		*dst = result;
	return err;
}