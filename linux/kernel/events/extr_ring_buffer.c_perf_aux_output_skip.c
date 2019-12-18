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
struct ring_buffer {unsigned long aux_head; scalar_t__ aux_watermark; scalar_t__ aux_wakeup; TYPE_1__* user_page; } ;
struct perf_output_handle {unsigned long size; unsigned long head; scalar_t__ wakeup; struct ring_buffer* rb; } ;
struct TYPE_2__ {int /*<<< orphan*/  aux_head; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  perf_output_wakeup (struct perf_output_handle*) ; 
 scalar_t__ rb_need_aux_wakeup (struct ring_buffer*) ; 

int perf_aux_output_skip(struct perf_output_handle *handle, unsigned long size)
{
	struct ring_buffer *rb = handle->rb;

	if (size > handle->size)
		return -ENOSPC;

	rb->aux_head += size;

	WRITE_ONCE(rb->user_page->aux_head, rb->aux_head);
	if (rb_need_aux_wakeup(rb)) {
		perf_output_wakeup(handle);
		handle->wakeup = rb->aux_wakeup + rb->aux_watermark;
	}

	handle->head = rb->aux_head;
	handle->size -= size;

	return 0;
}