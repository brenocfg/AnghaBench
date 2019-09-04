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
struct vm_area_struct {int vm_end; int vm_start; struct page** vm_private_data; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 int XEN_PAGE_SHIFT ; 
 int /*<<< orphan*/  free_xenballooned_pages (int,struct page**) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  pr_crit (char*,int,int) ; 
 int vma_pages (struct vm_area_struct*) ; 
 int /*<<< orphan*/  xen_feature (int /*<<< orphan*/ ) ; 
 int xen_unmap_domain_gfn_range (struct vm_area_struct*,int,struct page**) ; 

__attribute__((used)) static void privcmd_close(struct vm_area_struct *vma)
{
	struct page **pages = vma->vm_private_data;
	int numpgs = vma_pages(vma);
	int numgfns = (vma->vm_end - vma->vm_start) >> XEN_PAGE_SHIFT;
	int rc;

	if (!xen_feature(XENFEAT_auto_translated_physmap) || !numpgs || !pages)
		return;

	rc = xen_unmap_domain_gfn_range(vma, numgfns, pages);
	if (rc == 0)
		free_xenballooned_pages(numpgs, pages);
	else
		pr_crit("unable to unmap MFN range: leaking %d pages. rc=%d\n",
			numpgs, rc);
	kfree(pages);
}