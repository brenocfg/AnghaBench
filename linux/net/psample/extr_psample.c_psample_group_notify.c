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
struct psample_group {int /*<<< orphan*/  net; } ;
typedef  enum psample_command { ____Placeholder_psample_command } psample_command ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  PSAMPLE_NL_MCGRP_CONFIG ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int psample_group_nl_fill (struct sk_buff*,struct psample_group*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psample_nl_family ; 

__attribute__((used)) static void psample_group_notify(struct psample_group *group,
				 enum psample_command cmd)
{
	struct sk_buff *msg;
	int err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (!msg)
		return;

	err = psample_group_nl_fill(msg, group, cmd, 0, 0, NLM_F_MULTI);
	if (!err)
		genlmsg_multicast_netns(&psample_nl_family, group->net, msg, 0,
					PSAMPLE_NL_MCGRP_CONFIG, GFP_ATOMIC);
	else
		nlmsg_free(msg);
}