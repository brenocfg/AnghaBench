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
struct tipc_bearer {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TIPC_NLA_BEARER ; 
 int /*<<< orphan*/  TIPC_NLA_BEARER_MAX ; 
 size_t TIPC_NLA_BEARER_NAME ; 
 size_t TIPC_NLA_BEARER_UDP_OPTS ; 
 char* nla_data (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 struct tipc_bearer* tipc_bearer_find (struct net*,char*) ; 
 int /*<<< orphan*/  tipc_nl_bearer_policy ; 
 int tipc_udp_nl_bearer_add (struct tipc_bearer*,struct nlattr*) ; 

int tipc_nl_bearer_add(struct sk_buff *skb, struct genl_info *info)
{
	int err;
	char *name;
	struct tipc_bearer *b;
	struct nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];
	struct net *net = sock_net(skb->sk);

	if (!info->attrs[TIPC_NLA_BEARER])
		return -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_BEARER_MAX,
					  info->attrs[TIPC_NLA_BEARER],
					  tipc_nl_bearer_policy, info->extack);
	if (err)
		return err;

	if (!attrs[TIPC_NLA_BEARER_NAME])
		return -EINVAL;
	name = nla_data(attrs[TIPC_NLA_BEARER_NAME]);

	rtnl_lock();
	b = tipc_bearer_find(net, name);
	if (!b) {
		rtnl_unlock();
		return -EINVAL;
	}

#ifdef CONFIG_TIPC_MEDIA_UDP
	if (attrs[TIPC_NLA_BEARER_UDP_OPTS]) {
		err = tipc_udp_nl_bearer_add(b,
					     attrs[TIPC_NLA_BEARER_UDP_OPTS]);
		if (err) {
			rtnl_unlock();
			return err;
		}
	}
#endif
	rtnl_unlock();

	return 0;
}