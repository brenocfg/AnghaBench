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
struct vfio_iommu {int /*<<< orphan*/  notifier; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 

__attribute__((used)) static int vfio_iommu_type1_unregister_notifier(void *iommu_data,
						struct notifier_block *nb)
{
	struct vfio_iommu *iommu = iommu_data;

	return blocking_notifier_chain_unregister(&iommu->notifier, nb);
}