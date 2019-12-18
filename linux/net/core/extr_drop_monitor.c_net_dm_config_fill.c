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
 int /*<<< orphan*/  NET_DM_ATTR_ALERT_MODE ; 
 int /*<<< orphan*/  NET_DM_ATTR_QUEUE_LEN ; 
 int /*<<< orphan*/  NET_DM_ATTR_TRUNC_LEN ; 
 int /*<<< orphan*/  NET_DM_CMD_CONFIG_NEW ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_dm_alert_mode ; 
 int /*<<< orphan*/  net_dm_queue_len ; 
 int /*<<< orphan*/  net_dm_trunc_len ; 
 int /*<<< orphan*/  net_drop_monitor_family ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_dm_config_fill(struct sk_buff *msg, struct genl_info *info)
{
	void *hdr;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &net_drop_monitor_family, 0, NET_DM_CMD_CONFIG_NEW);
	if (!hdr)
		return -EMSGSIZE;

	if (nla_put_u8(msg, NET_DM_ATTR_ALERT_MODE, net_dm_alert_mode))
		goto nla_put_failure;

	if (nla_put_u32(msg, NET_DM_ATTR_TRUNC_LEN, net_dm_trunc_len))
		goto nla_put_failure;

	if (nla_put_u32(msg, NET_DM_ATTR_QUEUE_LEN, net_dm_queue_len))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);

	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}