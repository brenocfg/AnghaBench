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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ stage2_pud_addr_end (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stage2_pud_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stage2_pud_offset (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stage2_wp_pmds (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void  stage2_wp_puds(pgd_t *pgd, phys_addr_t addr, phys_addr_t end)
{
	pud_t *pud;
	phys_addr_t next;

	pud = stage2_pud_offset(pgd, addr);
	do {
		next = stage2_pud_addr_end(addr, end);
		if (!stage2_pud_none(*pud)) {
			/* TODO:PUD not supported, revisit later if supported */
			BUG_ON(stage2_pud_huge(*pud));
			stage2_wp_pmds(pud, addr, next);
		}
	} while (pud++, addr = next, addr != end);
}