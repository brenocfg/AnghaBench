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
struct vfio_iommu {int dummy; } ;
struct vfio_dma {unsigned long vaddr; int iommu_mapped; scalar_t__ size; int /*<<< orphan*/  prot; scalar_t__ iova; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 size_t rlimit (int /*<<< orphan*/ ) ; 
 int vfio_iommu_map (struct vfio_iommu*,scalar_t__,unsigned long,long,int /*<<< orphan*/ ) ; 
 long vfio_pin_pages_remote (struct vfio_dma*,scalar_t__,size_t,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  vfio_remove_dma (struct vfio_iommu*,struct vfio_dma*) ; 
 int /*<<< orphan*/  vfio_unpin_pages_remote (struct vfio_dma*,scalar_t__,unsigned long,long,int) ; 

__attribute__((used)) static int vfio_pin_map_dma(struct vfio_iommu *iommu, struct vfio_dma *dma,
			    size_t map_size)
{
	dma_addr_t iova = dma->iova;
	unsigned long vaddr = dma->vaddr;
	size_t size = map_size;
	long npage;
	unsigned long pfn, limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	int ret = 0;

	while (size) {
		/* Pin a contiguous chunk of memory */
		npage = vfio_pin_pages_remote(dma, vaddr + dma->size,
					      size >> PAGE_SHIFT, &pfn, limit);
		if (npage <= 0) {
			WARN_ON(!npage);
			ret = (int)npage;
			break;
		}

		/* Map it! */
		ret = vfio_iommu_map(iommu, iova + dma->size, pfn, npage,
				     dma->prot);
		if (ret) {
			vfio_unpin_pages_remote(dma, iova + dma->size, pfn,
						npage, true);
			break;
		}

		size -= npage << PAGE_SHIFT;
		dma->size += npage << PAGE_SHIFT;
	}

	dma->iommu_mapped = true;

	if (ret)
		vfio_remove_dma(iommu, dma);

	return ret;
}