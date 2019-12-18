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
struct dma_debug_entry {int /*<<< orphan*/  stack_entries; int /*<<< orphan*/  stack_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct dma_debug_entry* __dma_entry_alloc () ; 
 int /*<<< orphan*/  __dma_entry_alloc_check_leak () ; 
 scalar_t__ dma_debug_create_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_entries_lock ; 
 int global_disable ; 
 scalar_t__ num_free_entries ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stack_trace_save (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dma_debug_entry *dma_entry_alloc(void)
{
	struct dma_debug_entry *entry;
	unsigned long flags;

	spin_lock_irqsave(&free_entries_lock, flags);
	if (num_free_entries == 0) {
		if (dma_debug_create_entries(GFP_ATOMIC)) {
			global_disable = true;
			spin_unlock_irqrestore(&free_entries_lock, flags);
			pr_err("debugging out of memory - disabling\n");
			return NULL;
		}
		__dma_entry_alloc_check_leak();
	}

	entry = __dma_entry_alloc();

	spin_unlock_irqrestore(&free_entries_lock, flags);

#ifdef CONFIG_STACKTRACE
	entry->stack_len = stack_trace_save(entry->stack_entries,
					    ARRAY_SIZE(entry->stack_entries),
					    1);
#endif
	return entry;
}