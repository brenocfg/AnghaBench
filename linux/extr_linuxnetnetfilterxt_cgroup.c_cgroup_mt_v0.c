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
struct xt_cgroup_info_v0 {scalar_t__ id; int invert; } ;
struct xt_action_param {struct xt_cgroup_info_v0* matchinfo; } ;
struct sock {int /*<<< orphan*/  sk_cgrp_data; } ;
struct sk_buff {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 
 scalar_t__ sock_cgroup_classid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool
cgroup_mt_v0(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_cgroup_info_v0 *info = par->matchinfo;
	struct sock *sk = skb->sk;

	if (!sk || !sk_fullsock(sk) || !net_eq(xt_net(par), sock_net(sk)))
		return false;

	return (info->id == sock_cgroup_classid(&skb->sk->sk_cgrp_data)) ^
		info->invert;
}