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
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t TIPC_NLA_LINK_PROP ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_MAX ; 
 size_t TIPC_NLA_PROP_WIN ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int tipc_bc_link_set_queue_limits (struct net*,int /*<<< orphan*/ ) ; 
 int tipc_nl_parse_link_prop (struct nlattr*,struct nlattr**) ; 

int tipc_nl_bc_link_set(struct net *net, struct nlattr *attrs[])
{
	int err;
	u32 win;
	struct nlattr *props[TIPC_NLA_PROP_MAX + 1];

	if (!attrs[TIPC_NLA_LINK_PROP])
		return -EINVAL;

	err = tipc_nl_parse_link_prop(attrs[TIPC_NLA_LINK_PROP], props);
	if (err)
		return err;

	if (!props[TIPC_NLA_PROP_WIN])
		return -EOPNOTSUPP;

	win = nla_get_u32(props[TIPC_NLA_PROP_WIN]);

	return tipc_bc_link_set_queue_limits(net, win);
}