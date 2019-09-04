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
struct dma_debug_entry {int dummy; } ;

/* Variables and functions */
 struct dma_debug_entry* __dma_entry_alloc () ; 
 int /*<<< orphan*/  free_entries ; 
 int /*<<< orphan*/  free_entries_lock ; 
 int global_disable ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_debug_entry *dma_entry_alloc(void)
{
	struct dma_debug_entry *entry;
	unsigned long flags;

	spin_lock_irqsave(&free_entries_lock, flags);

	if (list_empty(&free_entries)) {
		global_disable = true;
		spin_unlock_irqrestore(&free_entries_lock, flags);
		pr_err("DMA-API: debugging out of memory - disabling\n");
		return NULL;
	}

	entry = __dma_entry_alloc();

	spin_unlock_irqrestore(&free_entries_lock, flags);

#ifdef CONFIG_STACKTRACE
	entry->stacktrace.max_entries = DMA_DEBUG_STACKTRACE_ENTRIES;
	entry->stacktrace.entries = entry->st_entries;
	entry->stacktrace.skip = 2;
	save_stack_trace(&entry->stacktrace);
#endif

	return entry;
}