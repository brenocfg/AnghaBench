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
struct vfio_group {int /*<<< orphan*/  iommu_group; } ;

/* Variables and functions */
 int iommu_group_id (int /*<<< orphan*/ ) ; 

int vfio_external_user_iommu_id(struct vfio_group *group)
{
	return iommu_group_id(group->iommu_group);
}