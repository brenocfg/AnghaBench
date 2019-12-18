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
struct dma_debug_entry {scalar_t__ direction; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 scalar_t__ active_cacheline_dec_overlap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_active_cacheline ; 
 int /*<<< orphan*/  radix_lock ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_cacheline_number (struct dma_debug_entry*) ; 

__attribute__((used)) static void active_cacheline_remove(struct dma_debug_entry *entry)
{
	phys_addr_t cln = to_cacheline_number(entry);
	unsigned long flags;

	/* ...mirror the insert case */
	if (entry->direction == DMA_TO_DEVICE)
		return;

	spin_lock_irqsave(&radix_lock, flags);
	/* since we are counting overlaps the final put of the
	 * cacheline will occur when the overlap count is 0.
	 * active_cacheline_dec_overlap() returns -1 in that case
	 */
	if (active_cacheline_dec_overlap(cln) < 0)
		radix_tree_delete(&dma_active_cacheline, cln);
	spin_unlock_irqrestore(&radix_lock, flags);
}