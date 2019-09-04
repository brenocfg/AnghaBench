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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */

__attribute__((used)) static pte_t move_soft_dirty_pte(pte_t pte)
{
	/*
	 * Set soft dirty bit so we can notice
	 * in userspace the ptes were moved.
	 */
#ifdef CONFIG_MEM_SOFT_DIRTY
	if (pte_present(pte))
		pte = pte_mksoft_dirty(pte);
	else if (is_swap_pte(pte))
		pte = pte_swp_mksoft_dirty(pte);
#endif
	return pte;
}