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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int FOLL_WRITE ; 
 unsigned long HPAGE_PMD_MASK ; 
 int /*<<< orphan*/  pmd_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkyoung (int /*<<< orphan*/ ) ; 
 scalar_t__ pmdp_set_access_flags (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_mmu_cache_pmd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void touch_pmd(struct vm_area_struct *vma, unsigned long addr,
		pmd_t *pmd, int flags)
{
	pmd_t _pmd;

	_pmd = pmd_mkyoung(*pmd);
	if (flags & FOLL_WRITE)
		_pmd = pmd_mkdirty(_pmd);
	if (pmdp_set_access_flags(vma, addr & HPAGE_PMD_MASK,
				pmd, _pmd, flags & FOLL_WRITE))
		update_mmu_cache_pmd(vma, addr, pmd);
}