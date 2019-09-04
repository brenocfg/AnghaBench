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
struct mdev_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mdev_detach_iommu(struct mdev_device *mdev)
{
	iommu_group_remove_device(&mdev->dev);
	dev_info(&mdev->dev, "MDEV: detaching iommu\n");
}