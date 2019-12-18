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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_page_prot; struct mm_struct* vm_mm; } ;
struct page_vma_mapped_walk {unsigned long address; int /*<<< orphan*/ * pte; struct vm_area_struct* vma; int /*<<< orphan*/  page; } ;
struct page {int dummy; } ;
struct mmu_notifier_range {int dummy; } ;
struct mm_struct {int dummy; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int /*<<< orphan*/  MM_ANONPAGES ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  compound_head (struct page*) ; 
 int /*<<< orphan*/  dec_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_cache_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  inc_mm_counter (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  lru_cache_add_active_or_unevictable (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 int mem_cgroup_try_charge (struct page*,struct mm_struct*,int /*<<< orphan*/ ,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_counter_file (struct page*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,struct mm_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  munlock_vma_page (struct page*) ; 
 int /*<<< orphan*/  page_add_new_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 int /*<<< orphan*/  page_remove_rmap (struct page*,int) ; 
 int /*<<< orphan*/  page_vma_mapped_walk (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/  page_vma_mapped_walk_done (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_clear_flush_notify (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pte_at_notify (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_to_free_swap (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int __replace_page(struct vm_area_struct *vma, unsigned long addr,
				struct page *old_page, struct page *new_page)
{
	struct mm_struct *mm = vma->vm_mm;
	struct page_vma_mapped_walk pvmw = {
		.page = compound_head(old_page),
		.vma = vma,
		.address = addr,
	};
	int err;
	struct mmu_notifier_range range;
	struct mem_cgroup *memcg;

	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm, addr,
				addr + PAGE_SIZE);

	if (new_page) {
		err = mem_cgroup_try_charge(new_page, vma->vm_mm, GFP_KERNEL,
					    &memcg, false);
		if (err)
			return err;
	}

	/* For try_to_free_swap() and munlock_vma_page() below */
	lock_page(old_page);

	mmu_notifier_invalidate_range_start(&range);
	err = -EAGAIN;
	if (!page_vma_mapped_walk(&pvmw)) {
		if (new_page)
			mem_cgroup_cancel_charge(new_page, memcg, false);
		goto unlock;
	}
	VM_BUG_ON_PAGE(addr != pvmw.address, old_page);

	if (new_page) {
		get_page(new_page);
		page_add_new_anon_rmap(new_page, vma, addr, false);
		mem_cgroup_commit_charge(new_page, memcg, false, false);
		lru_cache_add_active_or_unevictable(new_page, vma);
	} else
		/* no new page, just dec_mm_counter for old_page */
		dec_mm_counter(mm, MM_ANONPAGES);

	if (!PageAnon(old_page)) {
		dec_mm_counter(mm, mm_counter_file(old_page));
		inc_mm_counter(mm, MM_ANONPAGES);
	}

	flush_cache_page(vma, addr, pte_pfn(*pvmw.pte));
	ptep_clear_flush_notify(vma, addr, pvmw.pte);
	if (new_page)
		set_pte_at_notify(mm, addr, pvmw.pte,
				  mk_pte(new_page, vma->vm_page_prot));

	page_remove_rmap(old_page, false);
	if (!page_mapped(old_page))
		try_to_free_swap(old_page);
	page_vma_mapped_walk_done(&pvmw);

	if (vma->vm_flags & VM_LOCKED)
		munlock_vma_page(old_page);
	put_page(old_page);

	err = 0;
 unlock:
	mmu_notifier_invalidate_range_end(&range);
	unlock_page(old_page);
	return err;
}