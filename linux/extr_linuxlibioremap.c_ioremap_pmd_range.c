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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ALIGNED (scalar_t__,unsigned long) ; 
 unsigned long PMD_SIZE ; 
 int /*<<< orphan*/  init_mm ; 
 scalar_t__ ioremap_pmd_enabled () ; 
 scalar_t__ ioremap_pte_range (int /*<<< orphan*/ *,unsigned long,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_free_pte_page (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_set_huge (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ioremap_pmd_range(pud_t *pud, unsigned long addr,
		unsigned long end, phys_addr_t phys_addr, pgprot_t prot)
{
	pmd_t *pmd;
	unsigned long next;

	phys_addr -= addr;
	pmd = pmd_alloc(&init_mm, pud, addr);
	if (!pmd)
		return -ENOMEM;
	do {
		next = pmd_addr_end(addr, end);

		if (ioremap_pmd_enabled() &&
		    ((next - addr) == PMD_SIZE) &&
		    IS_ALIGNED(phys_addr + addr, PMD_SIZE) &&
		    pmd_free_pte_page(pmd, addr)) {
			if (pmd_set_huge(pmd, phys_addr + addr, prot))
				continue;
		}

		if (ioremap_pte_range(pmd, addr, next, phys_addr + addr, prot))
			return -ENOMEM;
	} while (pmd++, addr = next, addr != end);
	return 0;
}