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

/* Variables and functions */
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_entry (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 

unsigned long generic_max_swapfile_size(void)
{
	return swp_offset(pte_to_swp_entry(
			swp_entry_to_pte(swp_entry(0, ~0UL)))) + 1;
}