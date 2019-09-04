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

__attribute__((used)) static inline void dump_entry_trace(struct dma_debug_entry *entry)
{
#ifdef CONFIG_STACKTRACE
	if (entry) {
		pr_warning("Mapped at:\n");
		print_stack_trace(&entry->stacktrace, 0);
	}
#endif
}