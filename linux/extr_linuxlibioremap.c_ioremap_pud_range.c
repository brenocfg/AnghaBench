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
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ALIGNED (scalar_t__,unsigned long) ; 
 unsigned long PUD_SIZE ; 
 int /*<<< orphan*/  init_mm ; 
 scalar_t__ ioremap_pmd_range (int /*<<< orphan*/ *,unsigned long,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ioremap_pud_enabled () ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * pud_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_free_pmd_page (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_set_huge (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ioremap_pud_range(p4d_t *p4d, unsigned long addr,
		unsigned long end, phys_addr_t phys_addr, pgprot_t prot)
{
	pud_t *pud;
	unsigned long next;

	phys_addr -= addr;
	pud = pud_alloc(&init_mm, p4d, addr);
	if (!pud)
		return -ENOMEM;
	do {
		next = pud_addr_end(addr, end);

		if (ioremap_pud_enabled() &&
		    ((next - addr) == PUD_SIZE) &&
		    IS_ALIGNED(phys_addr + addr, PUD_SIZE) &&
		    pud_free_pmd_page(pud, addr)) {
			if (pud_set_huge(pud, phys_addr + addr, prot))
				continue;
		}

		if (ioremap_pmd_range(pud, addr, next, phys_addr + addr, prot))
			return -ENOMEM;
	} while (pud++, addr = next, addr != end);
	return 0;
}