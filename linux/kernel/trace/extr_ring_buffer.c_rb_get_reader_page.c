#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer_per_cpu {unsigned long last_overrun; unsigned long lost_events; int /*<<< orphan*/  lock; int /*<<< orphan*/  read_stamp; struct buffer_page* reader_page; int /*<<< orphan*/  pages_read; int /*<<< orphan*/  head_page; int /*<<< orphan*/  overrun; int /*<<< orphan*/  pages; struct buffer_page* commit_page; } ;
struct TYPE_6__ {TYPE_3__* next; int /*<<< orphan*/  prev; } ;
struct buffer_page {scalar_t__ read; TYPE_1__* page; TYPE_2__ list; scalar_t__ real_end; int /*<<< orphan*/  entries; int /*<<< orphan*/  write; } ;
struct TYPE_7__ {TYPE_2__* prev; } ;
struct TYPE_5__ {int /*<<< orphan*/  time_stamp; int /*<<< orphan*/  commit; } ;

/* Variables and functions */
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rb_head_page_replace (struct buffer_page*,struct buffer_page*) ; 
 int /*<<< orphan*/  rb_inc_page (struct ring_buffer_per_cpu*,int /*<<< orphan*/ *) ; 
 TYPE_3__* rb_list_head (TYPE_3__*) ; 
 scalar_t__ rb_num_of_entries (struct ring_buffer_per_cpu*) ; 
 scalar_t__ rb_page_size (struct buffer_page*) ; 
 struct buffer_page* rb_set_head_page (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_set_list_to_head (struct ring_buffer_per_cpu*,TYPE_2__*) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static struct buffer_page *
rb_get_reader_page(struct ring_buffer_per_cpu *cpu_buffer)
{
	struct buffer_page *reader = NULL;
	unsigned long overwrite;
	unsigned long flags;
	int nr_loops = 0;
	int ret;

	local_irq_save(flags);
	arch_spin_lock(&cpu_buffer->lock);

 again:
	/*
	 * This should normally only loop twice. But because the
	 * start of the reader inserts an empty page, it causes
	 * a case where we will loop three times. There should be no
	 * reason to loop four times (that I know of).
	 */
	if (RB_WARN_ON(cpu_buffer, ++nr_loops > 3)) {
		reader = NULL;
		goto out;
	}

	reader = cpu_buffer->reader_page;

	/* If there's more to read, return this page */
	if (cpu_buffer->reader_page->read < rb_page_size(reader))
		goto out;

	/* Never should we have an index greater than the size */
	if (RB_WARN_ON(cpu_buffer,
		       cpu_buffer->reader_page->read > rb_page_size(reader)))
		goto out;

	/* check if we caught up to the tail */
	reader = NULL;
	if (cpu_buffer->commit_page == cpu_buffer->reader_page)
		goto out;

	/* Don't bother swapping if the ring buffer is empty */
	if (rb_num_of_entries(cpu_buffer) == 0)
		goto out;

	/*
	 * Reset the reader page to size zero.
	 */
	local_set(&cpu_buffer->reader_page->write, 0);
	local_set(&cpu_buffer->reader_page->entries, 0);
	local_set(&cpu_buffer->reader_page->page->commit, 0);
	cpu_buffer->reader_page->real_end = 0;

 spin:
	/*
	 * Splice the empty reader page into the list around the head.
	 */
	reader = rb_set_head_page(cpu_buffer);
	if (!reader)
		goto out;
	cpu_buffer->reader_page->list.next = rb_list_head(reader->list.next);
	cpu_buffer->reader_page->list.prev = reader->list.prev;

	/*
	 * cpu_buffer->pages just needs to point to the buffer, it
	 *  has no specific buffer page to point to. Lets move it out
	 *  of our way so we don't accidentally swap it.
	 */
	cpu_buffer->pages = reader->list.prev;

	/* The reader page will be pointing to the new head */
	rb_set_list_to_head(cpu_buffer, &cpu_buffer->reader_page->list);

	/*
	 * We want to make sure we read the overruns after we set up our
	 * pointers to the next object. The writer side does a
	 * cmpxchg to cross pages which acts as the mb on the writer
	 * side. Note, the reader will constantly fail the swap
	 * while the writer is updating the pointers, so this
	 * guarantees that the overwrite recorded here is the one we
	 * want to compare with the last_overrun.
	 */
	smp_mb();
	overwrite = local_read(&(cpu_buffer->overrun));

	/*
	 * Here's the tricky part.
	 *
	 * We need to move the pointer past the header page.
	 * But we can only do that if a writer is not currently
	 * moving it. The page before the header page has the
	 * flag bit '1' set if it is pointing to the page we want.
	 * but if the writer is in the process of moving it
	 * than it will be '2' or already moved '0'.
	 */

	ret = rb_head_page_replace(reader, cpu_buffer->reader_page);

	/*
	 * If we did not convert it, then we must try again.
	 */
	if (!ret)
		goto spin;

	/*
	 * Yay! We succeeded in replacing the page.
	 *
	 * Now make the new head point back to the reader page.
	 */
	rb_list_head(reader->list.next)->prev = &cpu_buffer->reader_page->list;
	rb_inc_page(cpu_buffer, &cpu_buffer->head_page);

	local_inc(&cpu_buffer->pages_read);

	/* Finally update the reader page to the new head */
	cpu_buffer->reader_page = reader;
	cpu_buffer->reader_page->read = 0;

	if (overwrite != cpu_buffer->last_overrun) {
		cpu_buffer->lost_events = overwrite - cpu_buffer->last_overrun;
		cpu_buffer->last_overrun = overwrite;
	}

	goto again;

 out:
	/* Update the read_stamp on the first event */
	if (reader && reader->read == 0)
		cpu_buffer->read_stamp = reader->page->time_stamp;

	arch_spin_unlock(&cpu_buffer->lock);
	local_irq_restore(flags);

	return reader;
}