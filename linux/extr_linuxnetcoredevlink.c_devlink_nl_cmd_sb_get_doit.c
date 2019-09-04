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
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; struct devlink_sb** user_ptr; } ;
struct devlink_sb {int dummy; } ;
typedef  struct devlink_sb devlink ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_SB_NEW ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int devlink_nl_sb_fill (struct sk_buff*,struct devlink_sb*,struct devlink_sb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_sb_get_doit(struct sk_buff *skb,
				      struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	struct devlink_sb *devlink_sb = info->user_ptr[1];
	struct sk_buff *msg;
	int err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	err = devlink_nl_sb_fill(msg, devlink, devlink_sb,
				 DEVLINK_CMD_SB_NEW,
				 info->snd_portid, info->snd_seq, 0);
	if (err) {
		nlmsg_free(msg);
		return err;
	}

	return genlmsg_reply(msg, info);
}