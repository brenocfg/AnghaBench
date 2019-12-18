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
struct vm_fault {unsigned long address; int /*<<< orphan*/ * pmd; struct vm_area_struct* vma; } ;
struct vm_area_struct {int dummy; } ;
struct swap_info_struct {unsigned char* swap_map; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int FRONTSWAP_PAGES_UNUSED ; 
 int /*<<< orphan*/  GFP_HIGHUSER_MOVABLE ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned char volatile SWAP_MAP_BAD ; 
 int /*<<< orphan*/  frontswap_test (struct swap_info_struct*,unsigned long) ; 
 int /*<<< orphan*/  is_swap_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct swap_info_struct** swap_info ; 
 struct page* swapin_readahead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_fault*) ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 
 unsigned int swp_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_to_free_swap (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int unuse_pte (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static int unuse_pte_range(struct vm_area_struct *vma, pmd_t *pmd,
			unsigned long addr, unsigned long end,
			unsigned int type, bool frontswap,
			unsigned long *fs_pages_to_unuse)
{
	struct page *page;
	swp_entry_t entry;
	pte_t *pte;
	struct swap_info_struct *si;
	unsigned long offset;
	int ret = 0;
	volatile unsigned char *swap_map;

	si = swap_info[type];
	pte = pte_offset_map(pmd, addr);
	do {
		struct vm_fault vmf;

		if (!is_swap_pte(*pte))
			continue;

		entry = pte_to_swp_entry(*pte);
		if (swp_type(entry) != type)
			continue;

		offset = swp_offset(entry);
		if (frontswap && !frontswap_test(si, offset))
			continue;

		pte_unmap(pte);
		swap_map = &si->swap_map[offset];
		vmf.vma = vma;
		vmf.address = addr;
		vmf.pmd = pmd;
		page = swapin_readahead(entry, GFP_HIGHUSER_MOVABLE, &vmf);
		if (!page) {
			if (*swap_map == 0 || *swap_map == SWAP_MAP_BAD)
				goto try_next;
			return -ENOMEM;
		}

		lock_page(page);
		wait_on_page_writeback(page);
		ret = unuse_pte(vma, pmd, addr, entry, page);
		if (ret < 0) {
			unlock_page(page);
			put_page(page);
			goto out;
		}

		try_to_free_swap(page);
		unlock_page(page);
		put_page(page);

		if (*fs_pages_to_unuse && !--(*fs_pages_to_unuse)) {
			ret = FRONTSWAP_PAGES_UNUSED;
			goto out;
		}
try_next:
		pte = pte_offset_map(pmd, addr);
	} while (pte++, addr += PAGE_SIZE, addr != end);
	pte_unmap(pte - 1);

	ret = 0;
out:
	return ret;
}