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
struct netlink_ext_ack {int dummy; } ;
struct genl_info {struct netlink_ext_ack* extack; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int net_dm_alert_mode_set (struct genl_info*) ; 
 scalar_t__ net_dm_is_monitoring () ; 
 int /*<<< orphan*/  net_dm_queue_len_set (struct genl_info*) ; 
 int /*<<< orphan*/  net_dm_trunc_len_set (struct genl_info*) ; 

__attribute__((used)) static int net_dm_cmd_config(struct sk_buff *skb,
			struct genl_info *info)
{
	struct netlink_ext_ack *extack = info->extack;
	int rc;

	if (net_dm_is_monitoring()) {
		NL_SET_ERR_MSG_MOD(extack, "Cannot configure drop monitor during monitoring");
		return -EBUSY;
	}

	rc = net_dm_alert_mode_set(info);
	if (rc)
		return rc;

	net_dm_trunc_len_set(info);

	net_dm_queue_len_set(info);

	return 0;
}