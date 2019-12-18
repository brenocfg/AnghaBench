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
struct tcf_proto {int dummy; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int __tcf_ipt_init (struct net*,int /*<<< orphan*/ ,struct nlattr*,struct nlattr*,struct tc_action**,int /*<<< orphan*/ *,int,int,struct tcf_proto*) ; 
 int /*<<< orphan*/  act_xt_ops ; 
 int /*<<< orphan*/  xt_net_id ; 

__attribute__((used)) static int tcf_xt_init(struct net *net, struct nlattr *nla,
		       struct nlattr *est, struct tc_action **a, int ovr,
		       int bind, bool unlocked, struct tcf_proto *tp,
		       struct netlink_ext_ack *extack)
{
	return __tcf_ipt_init(net, xt_net_id, nla, est, a, &act_xt_ops, ovr,
			      bind, tp);
}