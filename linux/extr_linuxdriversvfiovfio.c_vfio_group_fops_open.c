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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct vfio_group {TYPE_1__ notifier; int /*<<< orphan*/  opened; scalar_t__ container; scalar_t__ noiommu; } ;
struct inode {int dummy; } ;
struct file {struct vfio_group* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (TYPE_1__*) ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EBUSY ; 
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 struct vfio_group* vfio_group_get_from_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_group_put (struct vfio_group*) ; 

__attribute__((used)) static int vfio_group_fops_open(struct inode *inode, struct file *filep)
{
	struct vfio_group *group;
	int opened;

	group = vfio_group_get_from_minor(iminor(inode));
	if (!group)
		return -ENODEV;

	if (group->noiommu && !capable(CAP_SYS_RAWIO)) {
		vfio_group_put(group);
		return -EPERM;
	}

	/* Do we need multiple instances of the group open?  Seems not. */
	opened = atomic_cmpxchg(&group->opened, 0, 1);
	if (opened) {
		vfio_group_put(group);
		return -EBUSY;
	}

	/* Is something still in use from a previous open? */
	if (group->container) {
		atomic_dec(&group->opened);
		vfio_group_put(group);
		return -EBUSY;
	}

	/* Warn if previous user didn't cleanup and re-init to drop them */
	if (WARN_ON(group->notifier.head))
		BLOCKING_INIT_NOTIFIER_HEAD(&group->notifier);

	filep->private_data = group;

	return 0;
}