#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/  vm_file; TYPE_1__* vm_ops; } ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_mkwrite; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  balance_dirty_pages_ratelimited (struct address_space*) ; 
 int /*<<< orphan*/  file_update_time (int /*<<< orphan*/ ) ; 
 struct address_space* page_rmapping (struct page*) ; 
 int set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void fault_dirty_shared_page(struct vm_area_struct *vma,
				    struct page *page)
{
	struct address_space *mapping;
	bool dirtied;
	bool page_mkwrite = vma->vm_ops && vma->vm_ops->page_mkwrite;

	dirtied = set_page_dirty(page);
	VM_BUG_ON_PAGE(PageAnon(page), page);
	/*
	 * Take a local copy of the address_space - page.mapping may be zeroed
	 * by truncate after unlock_page().   The address_space itself remains
	 * pinned by vma->vm_file's reference.  We rely on unlock_page()'s
	 * release semantics to prevent the compiler from undoing this copying.
	 */
	mapping = page_rmapping(page);
	unlock_page(page);

	if ((dirtied || page_mkwrite) && mapping) {
		/*
		 * Some device drivers do not set page.mapping
		 * but still dirty their pages
		 */
		balance_dirty_pages_ratelimited(mapping);
	}

	if (!page_mkwrite)
		file_update_time(vma->vm_file);
}