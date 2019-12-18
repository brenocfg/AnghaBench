#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ring_buffer_per_cpu {int /*<<< orphan*/  reader_lock; struct buffer_page* reader_page; struct buffer_page* tail_page; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; int /*<<< orphan*/  cpumask; } ;
struct buffer_page {TYPE_1__* page; } ;
struct TYPE_2__ {int /*<<< orphan*/  time_stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct buffer_page* rb_set_head_page (struct ring_buffer_per_cpu*) ; 

u64 ring_buffer_oldest_event_ts(struct ring_buffer *buffer, int cpu)
{
	unsigned long flags;
	struct ring_buffer_per_cpu *cpu_buffer;
	struct buffer_page *bpage;
	u64 ret = 0;

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		return 0;

	cpu_buffer = buffer->buffers[cpu];
	raw_spin_lock_irqsave(&cpu_buffer->reader_lock, flags);
	/*
	 * if the tail is on reader_page, oldest time stamp is on the reader
	 * page
	 */
	if (cpu_buffer->tail_page == cpu_buffer->reader_page)
		bpage = cpu_buffer->reader_page;
	else
		bpage = rb_set_head_page(cpu_buffer);
	if (bpage)
		ret = bpage->page->time_stamp;
	raw_spin_unlock_irqrestore(&cpu_buffer->reader_lock, flags);

	return ret;
}