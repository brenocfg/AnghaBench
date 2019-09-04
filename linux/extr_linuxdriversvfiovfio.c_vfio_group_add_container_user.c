#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfio_group {int /*<<< orphan*/  container_users; TYPE_1__* container; scalar_t__ noiommu; } ;
struct TYPE_2__ {int /*<<< orphan*/  iommu_driver; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_group_viable (struct vfio_group*) ; 

__attribute__((used)) static int vfio_group_add_container_user(struct vfio_group *group)
{
	if (!atomic_inc_not_zero(&group->container_users))
		return -EINVAL;

	if (group->noiommu) {
		atomic_dec(&group->container_users);
		return -EPERM;
	}
	if (!group->container->iommu_driver || !vfio_group_viable(group)) {
		atomic_dec(&group->container_users);
		return -EINVAL;
	}

	return 0;
}