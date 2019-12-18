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
struct mmu_notifier_range {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  __cond_lock (int /*<<< orphan*/ *,int) ; 
 int __follow_pte_pmd (struct mm_struct*,unsigned long,struct mmu_notifier_range*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

int follow_pte_pmd(struct mm_struct *mm, unsigned long address,
		   struct mmu_notifier_range *range,
		   pte_t **ptepp, pmd_t **pmdpp, spinlock_t **ptlp)
{
	int res;

	/* (void) is needed to make gcc happy */
	(void) __cond_lock(*ptlp,
			   !(res = __follow_pte_pmd(mm, address, range,
						    ptepp, pmdpp, ptlp)));
	return res;
}