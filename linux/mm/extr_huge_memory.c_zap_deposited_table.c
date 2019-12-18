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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;

/* Variables and functions */
 int /*<<< orphan*/  mm_dec_nr_ptes (struct mm_struct*) ; 
 int /*<<< orphan*/  pgtable_trans_huge_withdraw (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_free (struct mm_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void zap_deposited_table(struct mm_struct *mm, pmd_t *pmd)
{
	pgtable_t pgtable;

	pgtable = pgtable_trans_huge_withdraw(mm, pmd);
	pte_free(mm, pgtable);
	mm_dec_nr_ptes(mm);
}