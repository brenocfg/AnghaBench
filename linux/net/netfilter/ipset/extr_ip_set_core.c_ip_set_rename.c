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
struct ip_set {scalar_t__ ref; scalar_t__ ref_netlink; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ ip_set_id_t ;

/* Variables and functions */
 int ENOENT ; 
 size_t IPSET_ATTR_SETNAME ; 
 size_t IPSET_ATTR_SETNAME2 ; 
 int IPSET_ERR_EXIST_SETNAME2 ; 
 int IPSET_ERR_PROTOCOL ; 
 int IPSET_ERR_REFERENCED ; 
 int /*<<< orphan*/  IPSET_MAXNAMELEN ; 
 scalar_t__ STRNCMP (int /*<<< orphan*/ ,char const*) ; 
 struct ip_set* find_set (struct ip_set_net*,char*) ; 
 struct ip_set* ip_set (struct ip_set_net*,scalar_t__) ; 
 struct ip_set_net* ip_set_pernet (struct net*) ; 
 int /*<<< orphan*/  ip_set_ref_lock ; 
 char* nla_data (struct nlattr const* const) ; 
 scalar_t__ protocol_min_failed (struct nlattr const* const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip_set_rename(struct net *net, struct sock *ctnl,
			 struct sk_buff *skb, const struct nlmsghdr *nlh,
			 const struct nlattr * const attr[],
			 struct netlink_ext_ack *extack)
{
	struct ip_set_net *inst = ip_set_pernet(net);
	struct ip_set *set, *s;
	const char *name2;
	ip_set_id_t i;
	int ret = 0;

	if (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME] ||
		     !attr[IPSET_ATTR_SETNAME2]))
		return -IPSET_ERR_PROTOCOL;

	set = find_set(inst, nla_data(attr[IPSET_ATTR_SETNAME]));
	if (!set)
		return -ENOENT;

	write_lock_bh(&ip_set_ref_lock);
	if (set->ref != 0 || set->ref_netlink != 0) {
		ret = -IPSET_ERR_REFERENCED;
		goto out;
	}

	name2 = nla_data(attr[IPSET_ATTR_SETNAME2]);
	for (i = 0; i < inst->ip_set_max; i++) {
		s = ip_set(inst, i);
		if (s && STRNCMP(s->name, name2)) {
			ret = -IPSET_ERR_EXIST_SETNAME2;
			goto out;
		}
	}
	strncpy(set->name, name2, IPSET_MAXNAMELEN);

out:
	write_unlock_bh(&ip_set_ref_lock);
	return ret;
}