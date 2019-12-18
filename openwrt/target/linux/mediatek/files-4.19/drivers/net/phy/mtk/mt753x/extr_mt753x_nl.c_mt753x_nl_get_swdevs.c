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
struct gsw_mt753x {int dummy; } ;
struct genl_info {int dummy; } ;
typedef  int /*<<< orphan*/  dev_info ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MT753X_ATTR_TYPE_MESG ; 
 int /*<<< orphan*/  MT753X_CMD_REPLY ; 
 int mt753x_nl_list_devs (char*,int) ; 
 int mt753x_nl_prepare_reply (struct genl_info*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int mt753x_nl_send_reply (struct sk_buff*,struct genl_info*) ; 
 int nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int mt753x_nl_get_swdevs(struct genl_info *info, struct gsw_mt753x *gsw)
{
	struct sk_buff *rep_skb = NULL;
	char dev_info[512];
	int ret;

	ret = mt753x_nl_list_devs(dev_info, sizeof(dev_info));
	if (!ret) {
		pr_info("No switch registered\n");
		return -EINVAL;
	}

	ret = mt753x_nl_prepare_reply(info, MT753X_CMD_REPLY, &rep_skb);
	if (ret < 0)
		goto err;

	ret = nla_put_string(rep_skb, MT753X_ATTR_TYPE_MESG, dev_info);
	if (ret < 0)
		goto err;

	return mt753x_nl_send_reply(rep_skb, info);

err:
	if (rep_skb)
		nlmsg_free(rep_skb);

	return ret;
}