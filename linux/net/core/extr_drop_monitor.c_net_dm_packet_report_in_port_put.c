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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NET_DM_ATTR_IN_PORT ; 
 int /*<<< orphan*/  NET_DM_ATTR_PORT_NETDEV_IFINDEX ; 
 int /*<<< orphan*/  NET_DM_ATTR_PORT_NETDEV_NAME ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int net_dm_packet_report_in_port_put(struct sk_buff *msg, int ifindex,
					    const char *name)
{
	struct nlattr *attr;

	attr = nla_nest_start(msg, NET_DM_ATTR_IN_PORT);
	if (!attr)
		return -EMSGSIZE;

	if (ifindex &&
	    nla_put_u32(msg, NET_DM_ATTR_PORT_NETDEV_IFINDEX, ifindex))
		goto nla_put_failure;

	if (name && nla_put_string(msg, NET_DM_ATTR_PORT_NETDEV_NAME, name))
		goto nla_put_failure;

	nla_nest_end(msg, attr);

	return 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	return -EMSGSIZE;
}