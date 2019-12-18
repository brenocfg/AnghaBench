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
typedef  unsigned long phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned long) ; 
 unsigned long P4D_SIZE ; 
 int /*<<< orphan*/  ioremap_p4d_enabled () ; 
 int /*<<< orphan*/  p4d_free_pud_page (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ p4d_present (int /*<<< orphan*/ ) ; 
 int p4d_set_huge (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioremap_try_huge_p4d(p4d_t *p4d, unsigned long addr,
				unsigned long end, phys_addr_t phys_addr,
				pgprot_t prot)
{
	if (!ioremap_p4d_enabled())
		return 0;

	if ((end - addr) != P4D_SIZE)
		return 0;

	if (!IS_ALIGNED(addr, P4D_SIZE))
		return 0;

	if (!IS_ALIGNED(phys_addr, P4D_SIZE))
		return 0;

	if (p4d_present(*p4d) && !p4d_free_pud_page(p4d, addr))
		return 0;

	return p4d_set_huge(p4d, phys_addr, prot);
}