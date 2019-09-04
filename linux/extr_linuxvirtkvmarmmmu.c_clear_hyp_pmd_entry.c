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
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_thp_or_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_hyp_pmd_entry(pmd_t *pmd)
{
	pte_t *pte_table = pte_offset_kernel(pmd, 0);
	VM_BUG_ON(pmd_thp_or_huge(*pmd));
	pmd_clear(pmd);
	pte_free_kernel(NULL, pte_table);
	put_page(virt_to_page(pmd));
}