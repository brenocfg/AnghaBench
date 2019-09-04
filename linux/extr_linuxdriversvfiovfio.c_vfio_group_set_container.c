#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfio_iommu_driver {TYPE_2__* ops; } ;
struct vfio_group {scalar_t__ noiommu; int /*<<< orphan*/  container_users; int /*<<< orphan*/  container_next; struct vfio_container* container; int /*<<< orphan*/  iommu_group; } ;
struct vfio_container {scalar_t__ noiommu; int /*<<< orphan*/  group_lock; int /*<<< orphan*/  group_list; int /*<<< orphan*/  iommu_data; struct vfio_iommu_driver* iommu_driver; } ;
struct fd {TYPE_1__* file; } ;
struct TYPE_4__ {int (* attach_group ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct vfio_container* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EBADF ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_container_get (struct vfio_container*) ; 
 int /*<<< orphan*/  vfio_fops ; 

__attribute__((used)) static int vfio_group_set_container(struct vfio_group *group, int container_fd)
{
	struct fd f;
	struct vfio_container *container;
	struct vfio_iommu_driver *driver;
	int ret = 0;

	if (atomic_read(&group->container_users))
		return -EINVAL;

	if (group->noiommu && !capable(CAP_SYS_RAWIO))
		return -EPERM;

	f = fdget(container_fd);
	if (!f.file)
		return -EBADF;

	/* Sanity check, is this really our fd? */
	if (f.file->f_op != &vfio_fops) {
		fdput(f);
		return -EINVAL;
	}

	container = f.file->private_data;
	WARN_ON(!container); /* fget ensures we don't race vfio_release */

	down_write(&container->group_lock);

	/* Real groups and fake groups cannot mix */
	if (!list_empty(&container->group_list) &&
	    container->noiommu != group->noiommu) {
		ret = -EPERM;
		goto unlock_out;
	}

	driver = container->iommu_driver;
	if (driver) {
		ret = driver->ops->attach_group(container->iommu_data,
						group->iommu_group);
		if (ret)
			goto unlock_out;
	}

	group->container = container;
	container->noiommu = group->noiommu;
	list_add(&group->container_next, &container->group_list);

	/* Get a reference on the container and mark a user within the group */
	vfio_container_get(container);
	atomic_inc(&group->container_users);

unlock_out:
	up_write(&container->group_lock);
	fdput(f);
	return ret;
}