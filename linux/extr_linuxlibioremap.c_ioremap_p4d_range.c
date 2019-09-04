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
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ALIGNED (scalar_t__,unsigned long) ; 
 unsigned long P4D_SIZE ; 
 int /*<<< orphan*/  init_mm ; 
 scalar_t__ ioremap_p4d_enabled () ; 
 scalar_t__ ioremap_pud_range (int /*<<< orphan*/ *,unsigned long,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * p4d_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ p4d_set_huge (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ioremap_p4d_range(pgd_t *pgd, unsigned long addr,
		unsigned long end, phys_addr_t phys_addr, pgprot_t prot)
{
	p4d_t *p4d;
	unsigned long next;

	phys_addr -= addr;
	p4d = p4d_alloc(&init_mm, pgd, addr);
	if (!p4d)
		return -ENOMEM;
	do {
		next = p4d_addr_end(addr, end);

		if (ioremap_p4d_enabled() &&
		    ((next - addr) == P4D_SIZE) &&
		    IS_ALIGNED(phys_addr + addr, P4D_SIZE)) {
			if (p4d_set_huge(p4d, phys_addr + addr, prot))
				continue;
		}

		if (ioremap_pud_range(p4d, addr, next, phys_addr + addr, prot))
			return -ENOMEM;
	} while (p4d++, addr = next, addr != end);
	return 0;
}