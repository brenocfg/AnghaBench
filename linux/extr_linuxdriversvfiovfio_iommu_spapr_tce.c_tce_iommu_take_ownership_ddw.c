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
struct tce_container {struct iommu_table** tables; } ;
struct iommu_table_group {TYPE_1__* ops; } ;
struct iommu_table {int dummy; } ;
struct TYPE_2__ {long (* set_window ) (struct iommu_table_group*,long,struct iommu_table*) ;int /*<<< orphan*/  (* release_ownership ) (struct iommu_table_group*) ;int /*<<< orphan*/  (* unset_window ) (struct iommu_table_group*,long) ;int /*<<< orphan*/  (* take_ownership ) (struct iommu_table_group*) ;int /*<<< orphan*/  create_table; } ;

/* Variables and functions */
 long EFAULT ; 
 long IOMMU_TABLE_GROUP_MAX_TABLES ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  stub1 (struct iommu_table_group*) ; 
 long stub2 (struct iommu_table_group*,long,struct iommu_table*) ; 
 int /*<<< orphan*/  stub3 (struct iommu_table_group*,long) ; 
 int /*<<< orphan*/  stub4 (struct iommu_table_group*) ; 

__attribute__((used)) static long tce_iommu_take_ownership_ddw(struct tce_container *container,
		struct iommu_table_group *table_group)
{
	long i, ret = 0;

	if (!table_group->ops->create_table || !table_group->ops->set_window ||
			!table_group->ops->release_ownership) {
		WARN_ON_ONCE(1);
		return -EFAULT;
	}

	table_group->ops->take_ownership(table_group);

	/* Set all windows to the new group */
	for (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) {
		struct iommu_table *tbl = container->tables[i];

		if (!tbl)
			continue;

		ret = table_group->ops->set_window(table_group, i, tbl);
		if (ret)
			goto release_exit;
	}

	return 0;

release_exit:
	for (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i)
		table_group->ops->unset_window(table_group, i);

	table_group->ops->release_ownership(table_group);

	return ret;
}