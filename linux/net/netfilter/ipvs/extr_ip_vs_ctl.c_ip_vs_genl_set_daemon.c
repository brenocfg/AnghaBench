#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct netns_ipvs {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; TYPE_1__* genlhdr; } ;
struct TYPE_2__ {int cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IPVS_CMD_ATTR_DAEMON ; 
 int IPVS_CMD_DEL_DAEMON ; 
 int IPVS_CMD_NEW_DAEMON ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_MAX ; 
 int /*<<< orphan*/  ip_vs_daemon_policy ; 
 int ip_vs_genl_del_daemon (struct netns_ipvs*,struct nlattr**) ; 
 int ip_vs_genl_new_daemon (struct netns_ipvs*,struct nlattr**) ; 
 struct netns_ipvs* net_ipvs (struct net*) ; 
 scalar_t__ nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_genl_set_daemon(struct sk_buff *skb, struct genl_info *info)
{
	int ret = -EINVAL, cmd;
	struct net *net = sock_net(skb->sk);
	struct netns_ipvs *ipvs = net_ipvs(net);

	cmd = info->genlhdr->cmd;

	if (cmd == IPVS_CMD_NEW_DAEMON || cmd == IPVS_CMD_DEL_DAEMON) {
		struct nlattr *daemon_attrs[IPVS_DAEMON_ATTR_MAX + 1];

		if (!info->attrs[IPVS_CMD_ATTR_DAEMON] ||
		    nla_parse_nested_deprecated(daemon_attrs, IPVS_DAEMON_ATTR_MAX, info->attrs[IPVS_CMD_ATTR_DAEMON], ip_vs_daemon_policy, info->extack))
			goto out;

		if (cmd == IPVS_CMD_NEW_DAEMON)
			ret = ip_vs_genl_new_daemon(ipvs, daemon_attrs);
		else
			ret = ip_vs_genl_del_daemon(ipvs, daemon_attrs);
	}

out:
	return ret;
}