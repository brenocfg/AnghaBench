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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_mm; } ;
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 int /*<<< orphan*/  MM_SWAPENTS ; 
 int /*<<< orphan*/  activate_page (struct page*) ; 
 int /*<<< orphan*/  dec_mm_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  inc_mm_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* ksm_might_need_to_copy (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  lru_cache_add_active_or_unevictable (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 scalar_t__ mem_cgroup_try_charge (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_add_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  pte_mkold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_same_as_swp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int unuse_pte(struct vm_area_struct *vma, pmd_t *pmd,
		unsigned long addr, swp_entry_t entry, struct page *page)
{
	struct page *swapcache;
	struct mem_cgroup *memcg;
	spinlock_t *ptl;
	pte_t *pte;
	int ret = 1;

	swapcache = page;
	page = ksm_might_need_to_copy(page, vma, addr);
	if (unlikely(!page))
		return -ENOMEM;

	if (mem_cgroup_try_charge(page, vma->vm_mm, GFP_KERNEL,
				&memcg, false)) {
		ret = -ENOMEM;
		goto out_nolock;
	}

	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	if (unlikely(!pte_same_as_swp(*pte, swp_entry_to_pte(entry)))) {
		mem_cgroup_cancel_charge(page, memcg, false);
		ret = 0;
		goto out;
	}

	dec_mm_counter(vma->vm_mm, MM_SWAPENTS);
	inc_mm_counter(vma->vm_mm, MM_ANONPAGES);
	get_page(page);
	set_pte_at(vma->vm_mm, addr, pte,
		   pte_mkold(mk_pte(page, vma->vm_page_prot)));
	if (page == swapcache) {
		page_add_anon_rmap(page, vma, addr, false);
		mem_cgroup_commit_charge(page, memcg, true, false);
	} else { /* ksm created a completely new copy */
		page_add_new_anon_rmap(page, vma, addr, false);
		mem_cgroup_commit_charge(page, memcg, false, false);
		lru_cache_add_active_or_unevictable(page, vma);
	}
	swap_free(entry);
	/*
	 * Move the page to the active list so it is not
	 * immediately swapped out again after swapon.
	 */
	activate_page(page);
out:
	pte_unmap_unlock(pte, ptl);
out_nolock:
	if (page != swapcache) {
		unlock_page(page);
		put_page(page);
	}
	return ret;
}