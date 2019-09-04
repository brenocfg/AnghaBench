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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  clear_hyp_pgd_entry (int /*<<< orphan*/ *) ; 
 scalar_t__ hyp_pud_table_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ pud_addr_end (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  unmap_hyp_pmds (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void unmap_hyp_puds(pgd_t *pgd, phys_addr_t addr, phys_addr_t end)
{
	phys_addr_t next;
	pud_t *pud, *start_pud;

	start_pud = pud = pud_offset(pgd, addr);
	do {
		next = pud_addr_end(addr, end);
		/* Hyp doesn't use huge puds */
		if (!pud_none(*pud))
			unmap_hyp_pmds(pud, addr, next);
	} while (pud++, addr = next, addr != end);

	if (hyp_pud_table_empty(start_pud))
		clear_hyp_pgd_entry(pgd);
}