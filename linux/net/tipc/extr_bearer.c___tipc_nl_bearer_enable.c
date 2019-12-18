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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TIPC_MEDIA_LINK_PRI ; 
 size_t TIPC_NLA_BEARER ; 
 size_t TIPC_NLA_BEARER_DOMAIN ; 
 int /*<<< orphan*/  TIPC_NLA_BEARER_MAX ; 
 size_t TIPC_NLA_BEARER_NAME ; 
 size_t TIPC_NLA_BEARER_PROP ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_MAX ; 
 size_t TIPC_NLA_PROP_PRIO ; 
 char* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int tipc_enable_bearer (struct net*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlattr**) ; 
 int /*<<< orphan*/  tipc_nl_bearer_policy ; 
 int tipc_nl_parse_link_prop (struct nlattr*,struct nlattr**) ; 

int __tipc_nl_bearer_enable(struct sk_buff *skb, struct genl_info *info)
{
	int err;
	char *bearer;
	struct nlattr *attrs[TIPC_NLA_BEARER_MAX + 1];
	struct net *net = sock_net(skb->sk);
	u32 domain = 0;
	u32 prio;

	prio = TIPC_MEDIA_LINK_PRI;

	if (!info->attrs[TIPC_NLA_BEARER])
		return -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_BEARER_MAX,
					  info->attrs[TIPC_NLA_BEARER],
					  tipc_nl_bearer_policy, info->extack);
	if (err)
		return err;

	if (!attrs[TIPC_NLA_BEARER_NAME])
		return -EINVAL;

	bearer = nla_data(attrs[TIPC_NLA_BEARER_NAME]);

	if (attrs[TIPC_NLA_BEARER_DOMAIN])
		domain = nla_get_u32(attrs[TIPC_NLA_BEARER_DOMAIN]);

	if (attrs[TIPC_NLA_BEARER_PROP]) {
		struct nlattr *props[TIPC_NLA_PROP_MAX + 1];

		err = tipc_nl_parse_link_prop(attrs[TIPC_NLA_BEARER_PROP],
					      props);
		if (err)
			return err;

		if (props[TIPC_NLA_PROP_PRIO])
			prio = nla_get_u32(props[TIPC_NLA_PROP_PRIO]);
	}

	return tipc_enable_bearer(net, bearer, domain, prio, attrs);
}