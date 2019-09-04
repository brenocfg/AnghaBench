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
struct vfio_domain {int prot; int fgsp; int /*<<< orphan*/  domain; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 struct page* alloc_pages (int,int) ; 
 int get_order (int) ; 
 int iommu_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 size_t iommu_unmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 

__attribute__((used)) static void vfio_test_domain_fgsp(struct vfio_domain *domain)
{
	struct page *pages;
	int ret, order = get_order(PAGE_SIZE * 2);

	pages = alloc_pages(GFP_KERNEL | __GFP_ZERO, order);
	if (!pages)
		return;

	ret = iommu_map(domain->domain, 0, page_to_phys(pages), PAGE_SIZE * 2,
			IOMMU_READ | IOMMU_WRITE | domain->prot);
	if (!ret) {
		size_t unmapped = iommu_unmap(domain->domain, 0, PAGE_SIZE);

		if (unmapped == PAGE_SIZE)
			iommu_unmap(domain->domain, PAGE_SIZE, PAGE_SIZE);
		else
			domain->fgsp = true;
	}

	__free_pages(pages, order);
}