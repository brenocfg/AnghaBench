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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct mempolicy {int dummy; } ;
struct hstate {scalar_t__ free_huge_pages; scalar_t__ resv_huge_pages; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 struct page* dequeue_huge_page_nodemask (struct hstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htlb_alloc_mask (struct hstate*) ; 
 int huge_node (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,struct mempolicy**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mpol_cond_put (struct mempolicy*) ; 
 scalar_t__ vma_has_reserves (struct vm_area_struct*,long) ; 

__attribute__((used)) static struct page *dequeue_huge_page_vma(struct hstate *h,
				struct vm_area_struct *vma,
				unsigned long address, int avoid_reserve,
				long chg)
{
	struct page *page;
	struct mempolicy *mpol;
	gfp_t gfp_mask;
	nodemask_t *nodemask;
	int nid;

	/*
	 * A child process with MAP_PRIVATE mappings created by their parent
	 * have no page reserves. This check ensures that reservations are
	 * not "stolen". The child may still get SIGKILLed
	 */
	if (!vma_has_reserves(vma, chg) &&
			h->free_huge_pages - h->resv_huge_pages == 0)
		goto err;

	/* If reserves cannot be used, ensure enough pages are in the pool */
	if (avoid_reserve && h->free_huge_pages - h->resv_huge_pages == 0)
		goto err;

	gfp_mask = htlb_alloc_mask(h);
	nid = huge_node(vma, address, gfp_mask, &mpol, &nodemask);
	page = dequeue_huge_page_nodemask(h, gfp_mask, nid, nodemask);
	if (page && !avoid_reserve && vma_has_reserves(vma, chg)) {
		SetPagePrivate(page);
		h->resv_huge_pages--;
	}

	mpol_cond_put(mpol);
	return page;

err:
	return NULL;
}