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
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct page* alloc_surplus_huge_page (struct hstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htlb_alloc_mask (struct hstate*) ; 
 int huge_node (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,struct mempolicy**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mpol_cond_put (struct mempolicy*) ; 

__attribute__((used)) static
struct page *alloc_buddy_huge_page_with_mpol(struct hstate *h,
		struct vm_area_struct *vma, unsigned long addr)
{
	struct page *page;
	struct mempolicy *mpol;
	gfp_t gfp_mask = htlb_alloc_mask(h);
	int nid;
	nodemask_t *nodemask;

	nid = huge_node(vma, addr, gfp_mask, &mpol, &nodemask);
	page = alloc_surplus_huge_page(h, gfp_mask, nid, nodemask);
	mpol_cond_put(mpol);

	return page;
}