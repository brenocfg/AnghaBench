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
struct vm_fault {unsigned long address; struct vm_area_struct* vma; } ;
struct vm_area_struct {int dummy; } ;
struct swap_info_struct {unsigned long max; } ;
struct page {int dummy; } ;
struct blk_plug {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_RA ; 
 int /*<<< orphan*/  SetPageReadahead (struct page*) ; 
 struct page* __read_swap_cache_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int*) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_swap_cache_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  swap_readpage (struct page*,int) ; 
 int swapin_nr_pages (unsigned long) ; 
 int /*<<< orphan*/  swp_entry (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 
 struct swap_info_struct* swp_swap_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_type (int /*<<< orphan*/ ) ; 

struct page *swap_cluster_readahead(swp_entry_t entry, gfp_t gfp_mask,
				struct vm_fault *vmf)
{
	struct page *page;
	unsigned long entry_offset = swp_offset(entry);
	unsigned long offset = entry_offset;
	unsigned long start_offset, end_offset;
	unsigned long mask;
	struct swap_info_struct *si = swp_swap_info(entry);
	struct blk_plug plug;
	bool do_poll = true, page_allocated;
	struct vm_area_struct *vma = vmf->vma;
	unsigned long addr = vmf->address;

	mask = swapin_nr_pages(offset) - 1;
	if (!mask)
		goto skip;

	do_poll = false;
	/* Read a page_cluster sized and aligned cluster around offset. */
	start_offset = offset & ~mask;
	end_offset = offset | mask;
	if (!start_offset)	/* First page is swap header. */
		start_offset++;
	if (end_offset >= si->max)
		end_offset = si->max - 1;

	blk_start_plug(&plug);
	for (offset = start_offset; offset <= end_offset ; offset++) {
		/* Ok, do the async read-ahead now */
		page = __read_swap_cache_async(
			swp_entry(swp_type(entry), offset),
			gfp_mask, vma, addr, &page_allocated);
		if (!page)
			continue;
		if (page_allocated) {
			swap_readpage(page, false);
			if (offset != entry_offset) {
				SetPageReadahead(page);
				count_vm_event(SWAP_RA);
			}
		}
		put_page(page);
	}
	blk_finish_plug(&plug);

	lru_add_drain();	/* Push any new pages onto the LRU now */
skip:
	return read_swap_cache_async(entry, gfp_mask, vma, addr, do_poll);
}