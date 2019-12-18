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
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct devlink** user_ptr; } ;
struct devlink_snapshot {int dummy; } ;
struct devlink_region {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_REGION_NAME ; 
 size_t DEVLINK_ATTR_REGION_SNAPSHOT_ID ; 
 int EINVAL ; 
 struct devlink_region* devlink_region_get_by_name (struct devlink*,char const*) ; 
 int /*<<< orphan*/  devlink_region_snapshot_del (struct devlink_region*,struct devlink_snapshot*) ; 
 struct devlink_snapshot* devlink_region_snapshot_get_by_id (struct devlink_region*,int /*<<< orphan*/ ) ; 
 char* nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_region_del(struct sk_buff *skb,
				     struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	struct devlink_snapshot *snapshot;
	struct devlink_region *region;
	const char *region_name;
	u32 snapshot_id;

	if (!info->attrs[DEVLINK_ATTR_REGION_NAME] ||
	    !info->attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID])
		return -EINVAL;

	region_name = nla_data(info->attrs[DEVLINK_ATTR_REGION_NAME]);
	snapshot_id = nla_get_u32(info->attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID]);

	region = devlink_region_get_by_name(devlink, region_name);
	if (!region)
		return -EINVAL;

	snapshot = devlink_region_snapshot_get_by_id(region, snapshot_id);
	if (!snapshot)
		return -EINVAL;

	devlink_region_snapshot_del(region, snapshot);
	return 0;
}