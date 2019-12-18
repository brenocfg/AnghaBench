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
typedef  unsigned long phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned long) ; 
 unsigned long PUD_SIZE ; 
 int /*<<< orphan*/  ioremap_pud_enabled () ; 
 int /*<<< orphan*/  pud_free_pmd_page (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_present (int /*<<< orphan*/ ) ; 
 int pud_set_huge (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioremap_try_huge_pud(pud_t *pud, unsigned long addr,
				unsigned long end, phys_addr_t phys_addr,
				pgprot_t prot)
{
	if (!ioremap_pud_enabled())
		return 0;

	if ((end - addr) != PUD_SIZE)
		return 0;

	if (!IS_ALIGNED(addr, PUD_SIZE))
		return 0;

	if (!IS_ALIGNED(phys_addr, PUD_SIZE))
		return 0;

	if (pud_present(*pud) && !pud_free_pmd_page(pud, addr))
		return 0;

	return pud_set_huge(pud, phys_addr, prot);
}