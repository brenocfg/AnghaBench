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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct ip_set_net {scalar_t__ ip_set_max; } ;
struct ip_set {int dummy; } ;
typedef  scalar_t__ ip_set_id_t ;

/* Variables and functions */
 int ENOENT ; 
 size_t IPSET_ATTR_SETNAME ; 
 int IPSET_ERR_PROTOCOL ; 
 struct ip_set* find_set (struct ip_set_net*,int /*<<< orphan*/ ) ; 
 struct ip_set* ip_set (struct ip_set_net*,scalar_t__) ; 
 int /*<<< orphan*/  ip_set_flush_set (struct ip_set*) ; 
 struct ip_set_net* ip_set_pernet (struct net*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  protocol_min_failed (struct nlattr const* const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_set_flush(struct net *net, struct sock *ctnl, struct sk_buff *skb,
			const struct nlmsghdr *nlh,
			const struct nlattr * const attr[],
			struct netlink_ext_ack *extack)
{
	struct ip_set_net *inst = ip_set_pernet(net);
	struct ip_set *s;
	ip_set_id_t i;

	if (unlikely(protocol_min_failed(attr)))
		return -IPSET_ERR_PROTOCOL;

	if (!attr[IPSET_ATTR_SETNAME]) {
		for (i = 0; i < inst->ip_set_max; i++) {
			s = ip_set(inst, i);
			if (s)
				ip_set_flush_set(s);
		}
	} else {
		s = find_set(inst, nla_data(attr[IPSET_ATTR_SETNAME]));
		if (!s)
			return -ENOENT;

		ip_set_flush_set(s);
	}

	return 0;
}