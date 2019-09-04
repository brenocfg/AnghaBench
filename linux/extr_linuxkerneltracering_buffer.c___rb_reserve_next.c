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
struct ring_buffer_per_cpu {int /*<<< orphan*/  entries_bytes; int /*<<< orphan*/  buffer; int /*<<< orphan*/  tail_page; } ;
struct ring_buffer_event {int dummy; } ;
struct rb_event_info {int add_timestamp; unsigned long length; int /*<<< orphan*/  ts; scalar_t__ delta; struct buffer_page* tail_page; } ;
struct buffer_page {TYPE_1__* page; int /*<<< orphan*/  entries; int /*<<< orphan*/  write; } ;
struct TYPE_2__ {int /*<<< orphan*/  time_stamp; } ;

/* Variables and functions */
 unsigned long BUF_PAGE_SIZE ; 
 scalar_t__ RB_LEN_TIME_EXTEND ; 
 unsigned long RB_WRITE_MASK ; 
 struct buffer_page* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct ring_buffer_event* __rb_page_index (struct buffer_page*,unsigned long) ; 
 int /*<<< orphan*/  local_add (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long local_add_return (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_inc (int /*<<< orphan*/ *) ; 
 struct ring_buffer_event* rb_move_tail (struct ring_buffer_per_cpu*,unsigned long,struct rb_event_info*) ; 
 int /*<<< orphan*/  rb_update_event (struct ring_buffer_per_cpu*,struct ring_buffer_event*,struct rb_event_info*) ; 
 int /*<<< orphan*/  ring_buffer_time_stamp_abs (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ring_buffer_event *
__rb_reserve_next(struct ring_buffer_per_cpu *cpu_buffer,
		  struct rb_event_info *info)
{
	struct ring_buffer_event *event;
	struct buffer_page *tail_page;
	unsigned long tail, write;

	/*
	 * If the time delta since the last event is too big to
	 * hold in the time field of the event, then we append a
	 * TIME EXTEND event ahead of the data event.
	 */
	if (unlikely(info->add_timestamp))
		info->length += RB_LEN_TIME_EXTEND;

	/* Don't let the compiler play games with cpu_buffer->tail_page */
	tail_page = info->tail_page = READ_ONCE(cpu_buffer->tail_page);
	write = local_add_return(info->length, &tail_page->write);

	/* set write to only the index of the write */
	write &= RB_WRITE_MASK;
	tail = write - info->length;

	/*
	 * If this is the first commit on the page, then it has the same
	 * timestamp as the page itself.
	 */
	if (!tail && !ring_buffer_time_stamp_abs(cpu_buffer->buffer))
		info->delta = 0;

	/* See if we shot pass the end of this buffer page */
	if (unlikely(write > BUF_PAGE_SIZE))
		return rb_move_tail(cpu_buffer, tail, info);

	/* We reserved something on the buffer */

	event = __rb_page_index(tail_page, tail);
	rb_update_event(cpu_buffer, event, info);

	local_inc(&tail_page->entries);

	/*
	 * If this is the first commit on the page, then update
	 * its timestamp.
	 */
	if (!tail)
		tail_page->page->time_stamp = info->ts;

	/* account for these added bytes */
	local_add(info->length, &cpu_buffer->entries_bytes);

	return event;
}