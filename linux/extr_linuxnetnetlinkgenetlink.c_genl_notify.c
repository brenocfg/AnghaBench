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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {struct sock* genl_sock; } ;
struct genl_info {int /*<<< orphan*/  snd_portid; scalar_t__ nlhdr; } ;
struct genl_family {scalar_t__ mcgrp_offset; scalar_t__ n_mcgrps; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  nlmsg_notify (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int nlmsg_report (scalar_t__) ; 

void genl_notify(const struct genl_family *family, struct sk_buff *skb,
		 struct genl_info *info, u32 group, gfp_t flags)
{
	struct net *net = genl_info_net(info);
	struct sock *sk = net->genl_sock;
	int report = 0;

	if (info->nlhdr)
		report = nlmsg_report(info->nlhdr);

	if (WARN_ON_ONCE(group >= family->n_mcgrps))
		return;
	group = family->mcgrp_offset + group;
	nlmsg_notify(sk, skb, info->snd_portid, group, report, flags);
}