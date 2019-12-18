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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  in6; } ;
struct ipvs_sync_daemon_cfg {scalar_t__ mcast_af; TYPE_1__ mcast_group; int /*<<< orphan*/  mcast_ttl; int /*<<< orphan*/  mcast_port; int /*<<< orphan*/  sync_maxlen; int /*<<< orphan*/  syncid; int /*<<< orphan*/  mcast_ifn; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  IPVS_CMD_ATTR_DAEMON ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_MCAST_GROUP ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_MCAST_GROUP6 ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_MCAST_IFN ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_MCAST_PORT ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_MCAST_TTL ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_STATE ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_SYNC_ID ; 
 int /*<<< orphan*/  IPVS_DAEMON_ATTR_SYNC_MAXLEN ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_genl_fill_daemon(struct sk_buff *skb, __u32 state,
				  struct ipvs_sync_daemon_cfg *c)
{
	struct nlattr *nl_daemon;

	nl_daemon = nla_nest_start_noflag(skb, IPVS_CMD_ATTR_DAEMON);
	if (!nl_daemon)
		return -EMSGSIZE;

	if (nla_put_u32(skb, IPVS_DAEMON_ATTR_STATE, state) ||
	    nla_put_string(skb, IPVS_DAEMON_ATTR_MCAST_IFN, c->mcast_ifn) ||
	    nla_put_u32(skb, IPVS_DAEMON_ATTR_SYNC_ID, c->syncid) ||
	    nla_put_u16(skb, IPVS_DAEMON_ATTR_SYNC_MAXLEN, c->sync_maxlen) ||
	    nla_put_u16(skb, IPVS_DAEMON_ATTR_MCAST_PORT, c->mcast_port) ||
	    nla_put_u8(skb, IPVS_DAEMON_ATTR_MCAST_TTL, c->mcast_ttl))
		goto nla_put_failure;
#ifdef CONFIG_IP_VS_IPV6
	if (c->mcast_af == AF_INET6) {
		if (nla_put_in6_addr(skb, IPVS_DAEMON_ATTR_MCAST_GROUP6,
				     &c->mcast_group.in6))
			goto nla_put_failure;
	} else
#endif
		if (c->mcast_af == AF_INET &&
		    nla_put_in_addr(skb, IPVS_DAEMON_ATTR_MCAST_GROUP,
				    c->mcast_group.ip))
			goto nla_put_failure;
	nla_nest_end(skb, nl_daemon);

	return 0;

nla_put_failure:
	nla_nest_cancel(skb, nl_daemon);
	return -EMSGSIZE;
}