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
typedef  int /*<<< orphan*/  swp_entry_t ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 scalar_t__ huge_pte_none (int /*<<< orphan*/ ) ; 
 scalar_t__ is_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ non_swap_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 

bool is_hugetlb_entry_migration(pte_t pte)
{
	swp_entry_t swp;

	if (huge_pte_none(pte) || pte_present(pte))
		return false;
	swp = pte_to_swp_entry(pte);
	if (non_swap_entry(swp) && is_migration_entry(swp))
		return true;
	else
		return false;
}