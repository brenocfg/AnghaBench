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
struct nla_policy {int dummy; } ;
struct genl_ops {int cmd; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/  nlhdr; } ;

/* Variables and functions */
#define  CGROUPSTATS_CMD_GET 129 
 int EINVAL ; 
 int /*<<< orphan*/  GENL_HDRLEN ; 
 int /*<<< orphan*/  TASKSTATS_CMD_ATTR_MAX ; 
#define  TASKSTATS_CMD_GET 128 
 struct nla_policy* cgroupstats_cmd_get_policy ; 
 int nlmsg_validate_deprecated (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nla_policy const*,int /*<<< orphan*/ ) ; 
 struct nla_policy* taskstats_cmd_get_policy ; 

__attribute__((used)) static int taskstats_pre_doit(const struct genl_ops *ops, struct sk_buff *skb,
			      struct genl_info *info)
{
	const struct nla_policy *policy = NULL;

	switch (ops->cmd) {
	case TASKSTATS_CMD_GET:
		policy = taskstats_cmd_get_policy;
		break;
	case CGROUPSTATS_CMD_GET:
		policy = cgroupstats_cmd_get_policy;
		break;
	default:
		return -EINVAL;
	}

	return nlmsg_validate_deprecated(info->nlhdr, GENL_HDRLEN,
					 TASKSTATS_CMD_ATTR_MAX, policy,
					 info->extack);
}