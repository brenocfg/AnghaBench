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
struct xt_cgroup_info_v1 {int invert_path; scalar_t__ classid; int invert_classid; struct cgroup* priv; } ;
struct xt_action_param {struct xt_cgroup_info_v1* matchinfo; } ;
struct sock_cgroup_data {int dummy; } ;
struct sock {struct sock_cgroup_data sk_cgrp_data; } ;
struct sk_buff {struct sock* sk; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int cgroup_is_descendant (int /*<<< orphan*/ ,struct cgroup*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 
 scalar_t__ sock_cgroup_classid (struct sock_cgroup_data*) ; 
 int /*<<< orphan*/  sock_cgroup_ptr (struct sock_cgroup_data*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool cgroup_mt_v1(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_cgroup_info_v1 *info = par->matchinfo;
	struct sock_cgroup_data *skcd = &skb->sk->sk_cgrp_data;
	struct cgroup *ancestor = info->priv;
	struct sock *sk = skb->sk;

	if (!sk || !sk_fullsock(sk) || !net_eq(xt_net(par), sock_net(sk)))
		return false;

	if (ancestor)
		return cgroup_is_descendant(sock_cgroup_ptr(skcd), ancestor) ^
			info->invert_path;
	else
		return (info->classid == sock_cgroup_classid(skcd)) ^
			info->invert_classid;
}