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
struct vfio_iommu_driver {TYPE_1__* ops; } ;
struct vfio_group {int /*<<< orphan*/  container_next; int /*<<< orphan*/  container_q; struct vfio_container* container; int /*<<< orphan*/  iommu_group; } ;
struct vfio_container {int /*<<< orphan*/  group_lock; int /*<<< orphan*/ * iommu_data; struct vfio_iommu_driver* iommu_driver; int /*<<< orphan*/  group_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* detach_group ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_container_put (struct vfio_container*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __vfio_group_unset_container(struct vfio_group *group)
{
	struct vfio_container *container = group->container;
	struct vfio_iommu_driver *driver;

	down_write(&container->group_lock);

	driver = container->iommu_driver;
	if (driver)
		driver->ops->detach_group(container->iommu_data,
					  group->iommu_group);

	group->container = NULL;
	wake_up(&group->container_q);
	list_del(&group->container_next);

	/* Detaching the last group deprivileges a container, remove iommu */
	if (driver && list_empty(&container->group_list)) {
		driver->ops->release(container->iommu_data);
		module_put(driver->ops->owner);
		container->iommu_driver = NULL;
		container->iommu_data = NULL;
	}

	up_write(&container->group_lock);

	vfio_container_put(container);
}