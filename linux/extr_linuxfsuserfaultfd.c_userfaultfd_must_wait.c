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
struct userfaultfd_ctx {struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  p4d_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool userfaultfd_must_wait(struct userfaultfd_ctx *ctx,
					 unsigned long address,
					 unsigned long flags,
					 unsigned long reason)
{
	struct mm_struct *mm = ctx->mm;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd, _pmd;
	pte_t *pte;
	bool ret = true;

	VM_BUG_ON(!rwsem_is_locked(&mm->mmap_sem));

	pgd = pgd_offset(mm, address);
	if (!pgd_present(*pgd))
		goto out;
	p4d = p4d_offset(pgd, address);
	if (!p4d_present(*p4d))
		goto out;
	pud = pud_offset(p4d, address);
	if (!pud_present(*pud))
		goto out;
	pmd = pmd_offset(pud, address);
	/*
	 * READ_ONCE must function as a barrier with narrower scope
	 * and it must be equivalent to:
	 *	_pmd = *pmd; barrier();
	 *
	 * This is to deal with the instability (as in
	 * pmd_trans_unstable) of the pmd.
	 */
	_pmd = READ_ONCE(*pmd);
	if (pmd_none(_pmd))
		goto out;

	ret = false;
	if (!pmd_present(_pmd))
		goto out;

	if (pmd_trans_huge(_pmd))
		goto out;

	/*
	 * the pmd is stable (as in !pmd_trans_unstable) so we can re-read it
	 * and use the standard pte_offset_map() instead of parsing _pmd.
	 */
	pte = pte_offset_map(pmd, address);
	/*
	 * Lockless access: we're in a wait_event so it's ok if it
	 * changes under us.
	 */
	if (pte_none(*pte))
		ret = true;
	pte_unmap(pte);

out:
	return ret;
}