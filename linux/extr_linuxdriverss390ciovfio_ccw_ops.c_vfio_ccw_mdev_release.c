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
struct vfio_ccw_private {int /*<<< orphan*/  nb; } ;
struct mdev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_IOMMU_NOTIFY ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdev_dev (struct mdev_device*) ; 
 int /*<<< orphan*/  mdev_parent_dev (struct mdev_device*) ; 
 int /*<<< orphan*/  vfio_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vfio_ccw_mdev_release(struct mdev_device *mdev)
{
	struct vfio_ccw_private *private =
		dev_get_drvdata(mdev_parent_dev(mdev));

	vfio_unregister_notifier(mdev_dev(mdev), VFIO_IOMMU_NOTIFY,
				 &private->nb);
}