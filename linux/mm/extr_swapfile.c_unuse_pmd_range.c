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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pmd_none_or_trans_huge_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int unuse_pte_range (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned int,int,unsigned long*) ; 

__attribute__((used)) static inline int unuse_pmd_range(struct vm_area_struct *vma, pud_t *pud,
				unsigned long addr, unsigned long end,
				unsigned int type, bool frontswap,
				unsigned long *fs_pages_to_unuse)
{
	pmd_t *pmd;
	unsigned long next;
	int ret;

	pmd = pmd_offset(pud, addr);
	do {
		cond_resched();
		next = pmd_addr_end(addr, end);
		if (pmd_none_or_trans_huge_or_clear_bad(pmd))
			continue;
		ret = unuse_pte_range(vma, pmd, addr, next, type,
				      frontswap, fs_pages_to_unuse);
		if (ret)
			return ret;
	} while (pmd++, addr = next, addr != end);
	return 0;
}