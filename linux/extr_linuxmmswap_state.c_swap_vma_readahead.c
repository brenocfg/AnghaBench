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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vma_swap_readahead {int win; unsigned int nr_pte; unsigned int offset; int /*<<< orphan*/ * ptes; int /*<<< orphan*/  member_0; } ;
struct vm_fault {int /*<<< orphan*/  address; struct vm_area_struct* vma; } ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct blk_plug {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_RA ; 
 int /*<<< orphan*/  SetPageReadahead (struct page*) ; 
 struct page* __read_swap_cache_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  non_swap_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_swap_cache_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap_ra_info (struct vm_fault*,struct vma_swap_readahead*) ; 
 int /*<<< orphan*/  swap_readpage (struct page*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *swap_vma_readahead(swp_entry_t fentry, gfp_t gfp_mask,
				       struct vm_fault *vmf)
{
	struct blk_plug plug;
	struct vm_area_struct *vma = vmf->vma;
	struct page *page;
	pte_t *pte, pentry;
	swp_entry_t entry;
	unsigned int i;
	bool page_allocated;
	struct vma_swap_readahead ra_info = {0,};

	swap_ra_info(vmf, &ra_info);
	if (ra_info.win == 1)
		goto skip;

	blk_start_plug(&plug);
	for (i = 0, pte = ra_info.ptes; i < ra_info.nr_pte;
	     i++, pte++) {
		pentry = *pte;
		if (pte_none(pentry))
			continue;
		if (pte_present(pentry))
			continue;
		entry = pte_to_swp_entry(pentry);
		if (unlikely(non_swap_entry(entry)))
			continue;
		page = __read_swap_cache_async(entry, gfp_mask, vma,
					       vmf->address, &page_allocated);
		if (!page)
			continue;
		if (page_allocated) {
			swap_readpage(page, false);
			if (i != ra_info.offset) {
				SetPageReadahead(page);
				count_vm_event(SWAP_RA);
			}
		}
		put_page(page);
	}
	blk_finish_plug(&plug);
	lru_add_drain();
skip:
	return read_swap_cache_async(fentry, gfp_mask, vma, vmf->address,
				     ra_info.win == 1);
}