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
struct devlink_resource {int /*<<< orphan*/  size_new; int /*<<< orphan*/  size; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 struct devlink_resource* devlink_resource_find (struct devlink*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int devlink_resource_size_get(struct devlink *devlink,
			      u64 resource_id,
			      u64 *p_resource_size)
{
	struct devlink_resource *resource;
	int err = 0;

	mutex_lock(&devlink->lock);
	resource = devlink_resource_find(devlink, NULL, resource_id);
	if (!resource) {
		err = -EINVAL;
		goto out;
	}
	*p_resource_size = resource->size_new;
	resource->size = resource->size_new;
out:
	mutex_unlock(&devlink->lock);
	return err;
}