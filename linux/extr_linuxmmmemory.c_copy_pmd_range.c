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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int copy_huge_pmd (struct mm_struct*,struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,struct vm_area_struct*) ; 
 scalar_t__ copy_pte_range (struct mm_struct*,struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vm_area_struct*,unsigned long,unsigned long) ; 
 scalar_t__ is_swap_pmd (int /*<<< orphan*/ ) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int copy_pmd_range(struct mm_struct *dst_mm, struct mm_struct *src_mm,
		pud_t *dst_pud, pud_t *src_pud, struct vm_area_struct *vma,
		unsigned long addr, unsigned long end)
{
	pmd_t *src_pmd, *dst_pmd;
	unsigned long next;

	dst_pmd = pmd_alloc(dst_mm, dst_pud, addr);
	if (!dst_pmd)
		return -ENOMEM;
	src_pmd = pmd_offset(src_pud, addr);
	do {
		next = pmd_addr_end(addr, end);
		if (is_swap_pmd(*src_pmd) || pmd_trans_huge(*src_pmd)
			|| pmd_devmap(*src_pmd)) {
			int err;
			VM_BUG_ON_VMA(next-addr != HPAGE_PMD_SIZE, vma);
			err = copy_huge_pmd(dst_mm, src_mm,
					    dst_pmd, src_pmd, addr, vma);
			if (err == -ENOMEM)
				return -ENOMEM;
			if (!err)
				continue;
			/* fall through */
		}
		if (pmd_none_or_clear_bad(src_pmd))
			continue;
		if (copy_pte_range(dst_mm, src_mm, dst_pmd, src_pmd,
						vma, addr, next))
			return -ENOMEM;
	} while (dst_pmd++, src_pmd++, addr = next, addr != end);
	return 0;
}