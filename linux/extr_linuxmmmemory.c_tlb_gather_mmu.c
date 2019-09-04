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
struct mmu_gather {int /*<<< orphan*/  mm; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_tlb_gather_mmu (struct mmu_gather*,struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  inc_tlb_flush_pending (int /*<<< orphan*/ ) ; 

void tlb_gather_mmu(struct mmu_gather *tlb, struct mm_struct *mm,
			unsigned long start, unsigned long end)
{
	arch_tlb_gather_mmu(tlb, mm, start, end);
	inc_tlb_flush_pending(tlb->mm);
}