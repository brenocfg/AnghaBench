#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_5__ {int /*<<< orphan*/  page_table_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__ init_mm ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_populate_kernel (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_alloc_one_kernel (TYPE_1__*) ; 
 int /*<<< orphan*/  pte_free_kernel (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __pte_alloc_kernel(pmd_t *pmd)
{
	pte_t *new = pte_alloc_one_kernel(&init_mm);
	if (!new)
		return -ENOMEM;

	smp_wmb(); /* See comment in __pte_alloc */

	spin_lock(&init_mm.page_table_lock);
	if (likely(pmd_none(*pmd))) {	/* Has another populated it ? */
		pmd_populate_kernel(&init_mm, pmd, new);
		new = NULL;
	}
	spin_unlock(&init_mm.page_table_lock);
	if (new)
		pte_free_kernel(&init_mm, new);
	return 0;
}