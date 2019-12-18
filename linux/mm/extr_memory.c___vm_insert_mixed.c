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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIG_ARCH_HAS_PTE_SPECIAL ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int insert_page (struct vm_area_struct*,unsigned long,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_pfn (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfn_modify_allowed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_t_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_t_to_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_t_valid (int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  track_pfn_insert (struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_mixed_ok (struct vm_area_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t __vm_insert_mixed(struct vm_area_struct *vma,
		unsigned long addr, pfn_t pfn, bool mkwrite)
{
	pgprot_t pgprot = vma->vm_page_prot;
	int err;

	BUG_ON(!vm_mixed_ok(vma, pfn));

	if (addr < vma->vm_start || addr >= vma->vm_end)
		return VM_FAULT_SIGBUS;

	track_pfn_insert(vma, &pgprot, pfn);

	if (!pfn_modify_allowed(pfn_t_to_pfn(pfn), pgprot))
		return VM_FAULT_SIGBUS;

	/*
	 * If we don't have pte special, then we have to use the pfn_valid()
	 * based VM_MIXEDMAP scheme (see vm_normal_page), and thus we *must*
	 * refcount the page if pfn_valid is true (hence insert_page rather
	 * than insert_pfn).  If a zero_pfn were inserted into a VM_MIXEDMAP
	 * without pte special, it would there be refcounted as a normal page.
	 */
	if (!IS_ENABLED(CONFIG_ARCH_HAS_PTE_SPECIAL) &&
	    !pfn_t_devmap(pfn) && pfn_t_valid(pfn)) {
		struct page *page;

		/*
		 * At this point we are committed to insert_page()
		 * regardless of whether the caller specified flags that
		 * result in pfn_t_has_page() == false.
		 */
		page = pfn_to_page(pfn_t_to_pfn(pfn));
		err = insert_page(vma, addr, page, pgprot);
	} else {
		return insert_pfn(vma, addr, pfn, pgprot, mkwrite);
	}

	if (err == -ENOMEM)
		return VM_FAULT_OOM;
	if (err < 0 && err != -EBUSY)
		return VM_FAULT_SIGBUS;

	return VM_FAULT_NOPAGE;
}