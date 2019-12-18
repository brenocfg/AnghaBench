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
struct genl_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int net_dm_config_fill (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_dm_cmd_config_get(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *msg;
	int rc;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	rc = net_dm_config_fill(msg, info);
	if (rc)
		goto free_msg;

	return genlmsg_reply(msg, info);

free_msg:
	nlmsg_free(msg);
	return rc;
}