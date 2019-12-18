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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int stage2_ptep_test_and_clear_young (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stage2_pmdp_test_and_clear_young(pmd_t *pmd)
{
	return stage2_ptep_test_and_clear_young((pte_t *)pmd);
}