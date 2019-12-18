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
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NET_DM_CMD_STATS_NEW ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int net_dm_hw_stats_put (struct sk_buff*) ; 
 int net_dm_stats_put (struct sk_buff*) ; 
 int /*<<< orphan*/  net_drop_monitor_family ; 

__attribute__((used)) static int net_dm_stats_fill(struct sk_buff *msg, struct genl_info *info)
{
	void *hdr;
	int rc;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &net_drop_monitor_family, 0, NET_DM_CMD_STATS_NEW);
	if (!hdr)
		return -EMSGSIZE;

	rc = net_dm_stats_put(msg);
	if (rc)
		goto nla_put_failure;

	rc = net_dm_hw_stats_put(msg);
	if (rc)
		goto nla_put_failure;

	genlmsg_end(msg, hdr);

	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}