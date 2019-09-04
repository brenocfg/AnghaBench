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
struct vfio_domain {int /*<<< orphan*/  domain; } ;
struct vfio_dma {int dummy; } ;
typedef  size_t phys_addr_t ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  cond_resched () ; 
 size_t iommu_unmap (int /*<<< orphan*/ ,size_t,size_t) ; 
 scalar_t__ vfio_unpin_pages_remote (struct vfio_dma*,size_t,size_t,size_t,int) ; 

__attribute__((used)) static size_t unmap_unpin_slow(struct vfio_domain *domain,
			       struct vfio_dma *dma, dma_addr_t *iova,
			       size_t len, phys_addr_t phys,
			       long *unlocked)
{
	size_t unmapped = iommu_unmap(domain->domain, *iova, len);

	if (unmapped) {
		*unlocked += vfio_unpin_pages_remote(dma, *iova,
						     phys >> PAGE_SHIFT,
						     unmapped >> PAGE_SHIFT,
						     false);
		*iova += unmapped;
		cond_resched();
	}
	return unmapped;
}