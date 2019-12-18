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
struct devlink_resource {int /*<<< orphan*/ * occ_get_priv; int /*<<< orphan*/ * occ_get; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct devlink_resource* devlink_resource_find (struct devlink*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void devlink_resource_occ_get_unregister(struct devlink *devlink,
					 u64 resource_id)
{
	struct devlink_resource *resource;

	mutex_lock(&devlink->lock);
	resource = devlink_resource_find(devlink, NULL, resource_id);
	if (WARN_ON(!resource))
		goto out;
	WARN_ON(!resource->occ_get);

	resource->occ_get = NULL;
	resource->occ_get_priv = NULL;
out:
	mutex_unlock(&devlink->lock);
}