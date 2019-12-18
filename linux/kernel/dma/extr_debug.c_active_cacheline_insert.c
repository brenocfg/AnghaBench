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
 int EEXIST ; 
 int /*<<< orphan*/  active_cacheline_inc_overlap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_active_cacheline ; 
 int /*<<< orphan*/  radix_lock ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dma_debug_entry*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  to_cacheline_number (struct dma_debug_entry*) ; 

__attribute__((used)) static int active_cacheline_insert(struct dma_debug_entry *entry)
{
	phys_addr_t cln = to_cacheline_number(entry);
	unsigned long flags;
	int rc;

	/* If the device is not writing memory then we don't have any
	 * concerns about the cpu consuming stale data.  This mitigates
	 * legitimate usages of overlapping mappings.
	 */
	if (entry->direction == DMA_TO_DEVICE)
		return 0;

	spin_lock_irqsave(&radix_lock, flags);
	rc = radix_tree_insert(&dma_active_cacheline, cln, entry);
	if (rc == -EEXIST)
		active_cacheline_inc_overlap(cln);
	spin_unlock_irqrestore(&radix_lock, flags);

	return rc;
}