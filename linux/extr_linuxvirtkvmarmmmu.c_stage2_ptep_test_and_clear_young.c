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
 int /*<<< orphan*/  pte_mkold (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_young (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stage2_ptep_test_and_clear_young(pte_t *pte)
{
	if (pte_young(*pte)) {
		*pte = pte_mkold(*pte);
		return 1;
	}
	return 0;
}