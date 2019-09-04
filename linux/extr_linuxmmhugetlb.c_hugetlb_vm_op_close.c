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
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct resv_map {int /*<<< orphan*/  refs; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_RESV_OWNER ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 long hugepage_subpool_put_pages (struct hugepage_subpool*,unsigned long) ; 
 int /*<<< orphan*/  hugetlb_acct_memory (struct hstate*,long) ; 
 int /*<<< orphan*/  is_vma_resv_set (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long region_count (struct resv_map*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  resv_map_release ; 
 struct hugepage_subpool* subpool_vma (struct vm_area_struct*) ; 
 unsigned long vma_hugecache_offset (struct hstate*,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 struct resv_map* vma_resv_map (struct vm_area_struct*) ; 

__attribute__((used)) static void hugetlb_vm_op_close(struct vm_area_struct *vma)
{
	struct hstate *h = hstate_vma(vma);
	struct resv_map *resv = vma_resv_map(vma);
	struct hugepage_subpool *spool = subpool_vma(vma);
	unsigned long reserve, start, end;
	long gbl_reserve;

	if (!resv || !is_vma_resv_set(vma, HPAGE_RESV_OWNER))
		return;

	start = vma_hugecache_offset(h, vma, vma->vm_start);
	end = vma_hugecache_offset(h, vma, vma->vm_end);

	reserve = (end - start) - region_count(resv, start, end);

	kref_put(&resv->refs, resv_map_release);

	if (reserve) {
		/*
		 * Decrement reserve counts.  The global reserve count may be
		 * adjusted if the subpool has a minimum size.
		 */
		gbl_reserve = hugepage_subpool_put_pages(spool, reserve);
		hugetlb_acct_memory(h, -gbl_reserve);
	}
}