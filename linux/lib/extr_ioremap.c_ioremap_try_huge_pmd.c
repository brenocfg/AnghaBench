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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  unsigned long phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned long) ; 
 unsigned long PMD_SIZE ; 
 int /*<<< orphan*/  ioremap_pmd_enabled () ; 
 int /*<<< orphan*/  pmd_free_pte_page (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_present (int /*<<< orphan*/ ) ; 
 int pmd_set_huge (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioremap_try_huge_pmd(pmd_t *pmd, unsigned long addr,
				unsigned long end, phys_addr_t phys_addr,
				pgprot_t prot)
{
	if (!ioremap_pmd_enabled())
		return 0;

	if ((end - addr) != PMD_SIZE)
		return 0;

	if (!IS_ALIGNED(addr, PMD_SIZE))
		return 0;

	if (!IS_ALIGNED(phys_addr, PMD_SIZE))
		return 0;

	if (pmd_present(*pmd) && !pmd_free_pte_page(pmd, addr))
		return 0;

	return pmd_set_huge(pmd, phys_addr, prot);
}