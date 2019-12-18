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
struct mmu_gather {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tlb_batch_pages_flush (struct mmu_gather*) ; 
 int /*<<< orphan*/  tlb_table_flush (struct mmu_gather*) ; 

__attribute__((used)) static void tlb_flush_mmu_free(struct mmu_gather *tlb)
{
#ifdef CONFIG_HAVE_RCU_TABLE_FREE
	tlb_table_flush(tlb);
#endif
#ifndef CONFIG_HAVE_MMU_GATHER_NO_GATHER
	tlb_batch_pages_flush(tlb);
#endif
}