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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; struct devlink** user_ptr; } ;
struct devlink_resource {struct devlink_resource* parent; int /*<<< orphan*/  size_new; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_RESOURCE_ID ; 
 size_t DEVLINK_ATTR_RESOURCE_SIZE ; 
 int EINVAL ; 
 struct devlink_resource* devlink_resource_find (struct devlink*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_resource_validate_children (struct devlink_resource*) ; 
 int devlink_resource_validate_size (struct devlink_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_resource_set(struct sk_buff *skb,
				       struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	struct devlink_resource *resource;
	u64 resource_id;
	u64 size;
	int err;

	if (!info->attrs[DEVLINK_ATTR_RESOURCE_ID] ||
	    !info->attrs[DEVLINK_ATTR_RESOURCE_SIZE])
		return -EINVAL;
	resource_id = nla_get_u64(info->attrs[DEVLINK_ATTR_RESOURCE_ID]);

	resource = devlink_resource_find(devlink, NULL, resource_id);
	if (!resource)
		return -EINVAL;

	size = nla_get_u64(info->attrs[DEVLINK_ATTR_RESOURCE_SIZE]);
	err = devlink_resource_validate_size(resource, size, info->extack);
	if (err)
		return err;

	resource->size_new = size;
	devlink_resource_validate_children(resource);
	if (resource->parent)
		devlink_resource_validate_children(resource->parent);
	return 0;
}