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
struct tce_container {scalar_t__ v2; } ;
struct iommu_table {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_NONE ; 
 int /*<<< orphan*/  cond_resched () ; 
 long iommu_tce_xchg (struct iommu_table*,unsigned long,unsigned long*,int*) ; 
 int /*<<< orphan*/  tce_iommu_unuse_page (struct tce_container*,unsigned long) ; 
 int /*<<< orphan*/  tce_iommu_unuse_page_v2 (struct tce_container*,struct iommu_table*,unsigned long) ; 

__attribute__((used)) static int tce_iommu_clear(struct tce_container *container,
		struct iommu_table *tbl,
		unsigned long entry, unsigned long pages)
{
	unsigned long oldhpa;
	long ret;
	enum dma_data_direction direction;

	for ( ; pages; --pages, ++entry) {
		cond_resched();

		direction = DMA_NONE;
		oldhpa = 0;
		ret = iommu_tce_xchg(tbl, entry, &oldhpa, &direction);
		if (ret)
			continue;

		if (direction == DMA_NONE)
			continue;

		if (container->v2) {
			tce_iommu_unuse_page_v2(container, tbl, entry);
			continue;
		}

		tce_iommu_unuse_page(container, oldhpa);
	}

	return 0;
}