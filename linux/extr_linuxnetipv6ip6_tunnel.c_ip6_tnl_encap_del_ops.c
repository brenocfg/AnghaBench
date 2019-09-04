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
struct ip6_tnl_encap_ops {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 unsigned int MAX_IPTUN_ENCAP_OPS ; 
 struct ip6_tnl_encap_ops const* cmpxchg (struct ip6_tnl_encap_ops const**,struct ip6_tnl_encap_ops const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ip6tun_encaps ; 
 int /*<<< orphan*/  synchronize_net () ; 

int ip6_tnl_encap_del_ops(const struct ip6_tnl_encap_ops *ops,
			  unsigned int num)
{
	int ret;

	if (num >= MAX_IPTUN_ENCAP_OPS)
		return -ERANGE;

	ret = (cmpxchg((const struct ip6_tnl_encap_ops **)
		       &ip6tun_encaps[num],
		       ops, NULL) == ops) ? 0 : -1;

	synchronize_net();

	return ret;
}