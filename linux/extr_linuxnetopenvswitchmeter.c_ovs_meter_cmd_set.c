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
struct sk_buff {int /*<<< orphan*/  lock; scalar_t__ keep_stats; int /*<<< orphan*/  sk; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct nlattr {int dummy; } ;
struct genl_info {struct ovs_header* userhdr; struct nlattr** attrs; } ;
struct dp_meter {int /*<<< orphan*/  lock; scalar_t__ keep_stats; int /*<<< orphan*/  sk; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct sk_buff*) ; 
 size_t OVS_METER_ATTR_ID ; 
 int /*<<< orphan*/  OVS_METER_CMD_SET ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  attach_meter (struct datapath*,struct sk_buff*) ; 
 int /*<<< orphan*/  detach_meter (struct sk_buff*) ; 
 struct sk_buff* dp_meter_create (struct nlattr**) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,struct ovs_header*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 struct datapath* get_dp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sk_buff*) ; 
 struct sk_buff* lookup_meter (struct datapath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_put_u32 (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_lock () ; 
 struct sk_buff* ovs_meter_cmd_reply_start (struct genl_info*,int /*<<< orphan*/ ,struct ovs_header**) ; 
 int ovs_meter_cmd_reply_stats (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_meter_free (struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovs_meter_cmd_set(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **a = info->attrs;
	struct dp_meter *meter, *old_meter;
	struct sk_buff *reply;
	struct ovs_header *ovs_reply_header;
	struct ovs_header *ovs_header = info->userhdr;
	struct datapath *dp;
	int err;
	u32 meter_id;
	bool failed;

	if (!a[OVS_METER_ATTR_ID]) {
		return -ENODEV;
	}

	meter = dp_meter_create(a);
	if (IS_ERR_OR_NULL(meter))
		return PTR_ERR(meter);

	reply = ovs_meter_cmd_reply_start(info, OVS_METER_CMD_SET,
					  &ovs_reply_header);
	if (IS_ERR(reply)) {
		err = PTR_ERR(reply);
		goto exit_free_meter;
	}

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_ifindex);
	if (!dp) {
		err = -ENODEV;
		goto exit_unlock;
	}

	meter_id = nla_get_u32(a[OVS_METER_ATTR_ID]);

	/* Cannot fail after this. */
	old_meter = lookup_meter(dp, meter_id);
	detach_meter(old_meter);
	attach_meter(dp, meter);
	ovs_unlock();

	/* Build response with the meter_id and stats from
	 * the old meter, if any.
	 */
	failed = nla_put_u32(reply, OVS_METER_ATTR_ID, meter_id);
	WARN_ON(failed);
	if (old_meter) {
		spin_lock_bh(&old_meter->lock);
		if (old_meter->keep_stats) {
			err = ovs_meter_cmd_reply_stats(reply, meter_id,
							old_meter);
			WARN_ON(err);
		}
		spin_unlock_bh(&old_meter->lock);
		ovs_meter_free(old_meter);
	}

	genlmsg_end(reply, ovs_reply_header);
	return genlmsg_reply(reply, info);

exit_unlock:
	ovs_unlock();
	nlmsg_free(reply);
exit_free_meter:
	kfree(meter);
	return err;
}