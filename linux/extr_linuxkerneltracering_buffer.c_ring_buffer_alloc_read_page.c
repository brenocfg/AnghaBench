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
struct ring_buffer_per_cpu {int /*<<< orphan*/  lock; int /*<<< orphan*/ * free_page; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; int /*<<< orphan*/  cpumask; } ;
struct page {int dummy; } ;
typedef  void buffer_data_page ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 int __GFP_NORETRY ; 
 struct page* alloc_pages_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  rb_init_page (void*) ; 

void *ring_buffer_alloc_read_page(struct ring_buffer *buffer, int cpu)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	struct buffer_data_page *bpage = NULL;
	unsigned long flags;
	struct page *page;

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		return ERR_PTR(-ENODEV);

	cpu_buffer = buffer->buffers[cpu];
	local_irq_save(flags);
	arch_spin_lock(&cpu_buffer->lock);

	if (cpu_buffer->free_page) {
		bpage = cpu_buffer->free_page;
		cpu_buffer->free_page = NULL;
	}

	arch_spin_unlock(&cpu_buffer->lock);
	local_irq_restore(flags);

	if (bpage)
		goto out;

	page = alloc_pages_node(cpu_to_node(cpu),
				GFP_KERNEL | __GFP_NORETRY, 0);
	if (!page)
		return ERR_PTR(-ENOMEM);

	bpage = page_address(page);

 out:
	rb_init_page(bpage);

	return bpage;
}