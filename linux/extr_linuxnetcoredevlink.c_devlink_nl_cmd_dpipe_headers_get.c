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
struct genl_info {struct devlink** user_ptr; } ;
struct devlink {int /*<<< orphan*/  dpipe_headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_DPIPE_HEADERS_GET ; 
 int EOPNOTSUPP ; 
 int devlink_dpipe_headers_fill (struct genl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_dpipe_headers_get(struct sk_buff *skb,
					    struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];

	if (!devlink->dpipe_headers)
		return -EOPNOTSUPP;
	return devlink_dpipe_headers_fill(info, DEVLINK_CMD_DPIPE_HEADERS_GET,
					  0, devlink->dpipe_headers);
}