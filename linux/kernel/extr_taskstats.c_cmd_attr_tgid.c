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
struct taskstats {int dummy; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TASKSTATS_CMD_ATTR_TGID ; 
 int /*<<< orphan*/  TASKSTATS_CMD_NEW ; 
 int /*<<< orphan*/  TASKSTATS_TYPE_TGID ; 
 int fill_stats_for_tgid (int /*<<< orphan*/ ,struct taskstats*) ; 
 struct taskstats* mk_reply (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int prepare_reply (struct genl_info*,int /*<<< orphan*/ ,struct sk_buff**,size_t) ; 
 int send_reply (struct sk_buff*,struct genl_info*) ; 
 size_t taskstats_packet_size () ; 

__attribute__((used)) static int cmd_attr_tgid(struct genl_info *info)
{
	struct taskstats *stats;
	struct sk_buff *rep_skb;
	size_t size;
	u32 tgid;
	int rc;

	size = taskstats_packet_size();

	rc = prepare_reply(info, TASKSTATS_CMD_NEW, &rep_skb, size);
	if (rc < 0)
		return rc;

	rc = -EINVAL;
	tgid = nla_get_u32(info->attrs[TASKSTATS_CMD_ATTR_TGID]);
	stats = mk_reply(rep_skb, TASKSTATS_TYPE_TGID, tgid);
	if (!stats)
		goto err;

	rc = fill_stats_for_tgid(tgid, stats);
	if (rc < 0)
		goto err;
	return send_reply(rep_skb, info);
err:
	nlmsg_free(rep_skb);
	return rc;
}