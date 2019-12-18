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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  attrs; int /*<<< orphan*/  userhdr; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct datapath*) ; 
 int /*<<< orphan*/  OVS_DP_CMD_SET ; 
 int PTR_ERR (struct datapath*) ; 
 int /*<<< orphan*/  dp_datapath_genl_family ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct datapath* lookup_datapath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovs_dp_change (struct datapath*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ovs_dp_cmd_alloc_info () ; 
 int ovs_dp_cmd_fill_info (struct datapath*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_notify (int /*<<< orphan*/ *,struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_dp_cmd_set(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *reply;
	struct datapath *dp;
	int err;

	reply = ovs_dp_cmd_alloc_info();
	if (!reply)
		return -ENOMEM;

	ovs_lock();
	dp = lookup_datapath(sock_net(skb->sk), info->userhdr, info->attrs);
	err = PTR_ERR(dp);
	if (IS_ERR(dp))
		goto err_unlock_free;

	err = ovs_dp_change(dp, info->attrs);
	if (err)
		goto err_unlock_free;

	err = ovs_dp_cmd_fill_info(dp, reply, info->snd_portid,
				   info->snd_seq, 0, OVS_DP_CMD_SET);
	BUG_ON(err < 0);

	ovs_unlock();
	ovs_notify(&dp_datapath_genl_family, reply, info);

	return 0;

err_unlock_free:
	ovs_unlock();
	kfree_skb(reply);
	return err;
}