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
struct ring_buffer_per_cpu {int /*<<< orphan*/  lock; struct buffer_data_page* free_page; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; } ;
struct page {int dummy; } ;
struct buffer_data_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int page_ref_count (struct page*) ; 
 struct page* virt_to_page (struct buffer_data_page*) ; 

void ring_buffer_free_read_page(struct ring_buffer *buffer, int cpu, void *data)
{
	struct ring_buffer_per_cpu *cpu_buffer = buffer->buffers[cpu];
	struct buffer_data_page *bpage = data;
	struct page *page = virt_to_page(bpage);
	unsigned long flags;

	/* If the page is still in use someplace else, we can't reuse it */
	if (page_ref_count(page) > 1)
		goto out;

	local_irq_save(flags);
	arch_spin_lock(&cpu_buffer->lock);

	if (!cpu_buffer->free_page) {
		cpu_buffer->free_page = bpage;
		bpage = NULL;
	}

	arch_spin_unlock(&cpu_buffer->lock);
	local_irq_restore(flags);

 out:
	free_page((unsigned long)bpage);
}