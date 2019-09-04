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
typedef  int u64 ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  pfn_pte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_alloc_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioremap_pte_range(pmd_t *pmd, unsigned long addr,
		unsigned long end, phys_addr_t phys_addr, pgprot_t prot)
{
	pte_t *pte;
	u64 pfn;

	pfn = phys_addr >> PAGE_SHIFT;
	pte = pte_alloc_kernel(pmd, addr);
	if (!pte)
		return -ENOMEM;
	do {
		BUG_ON(!pte_none(*pte));
		set_pte_at(&init_mm, addr, pte, pfn_pte(pfn, prot));
		pfn++;
	} while (pte++, addr += PAGE_SIZE, addr != end);
	return 0;
}