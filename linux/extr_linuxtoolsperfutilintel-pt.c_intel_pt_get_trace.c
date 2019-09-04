#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_pt_queue {int stop; size_t queue_nr; struct auxtrace_buffer* old_buffer; scalar_t__ step_through_buffers; TYPE_3__* pt; struct auxtrace_buffer* buffer; } ;
struct intel_pt_buffer {int consecutive; int /*<<< orphan*/  len; scalar_t__ trace_nr; int /*<<< orphan*/  ref_timestamp; scalar_t__ buf; } ;
struct auxtrace_queue {int dummy; } ;
struct auxtrace_buffer {scalar_t__ buffer_nr; int /*<<< orphan*/  consecutive; int /*<<< orphan*/  reference; scalar_t__ data; int /*<<< orphan*/  size; scalar_t__ use_data; int /*<<< orphan*/  use_size; } ;
struct TYPE_4__ {struct auxtrace_queue* queue_array; } ;
struct TYPE_6__ {scalar_t__ sampling_mode; scalar_t__ snapshot_mode; TYPE_2__* session; TYPE_1__ queues; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  auxtrace_buffer__drop_data (struct auxtrace_buffer*) ; 
 scalar_t__ auxtrace_buffer__get_data (struct auxtrace_buffer*,int) ; 
 struct auxtrace_buffer* auxtrace_buffer__next (struct auxtrace_queue*,struct auxtrace_buffer*) ; 
 scalar_t__ intel_pt_do_fix_overlap (TYPE_3__*,struct auxtrace_buffer*,struct auxtrace_buffer*) ; 
 int perf_data__fd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_get_trace(struct intel_pt_buffer *b, void *data)
{
	struct intel_pt_queue *ptq = data;
	struct auxtrace_buffer *buffer = ptq->buffer;
	struct auxtrace_buffer *old_buffer = ptq->old_buffer;
	struct auxtrace_queue *queue;
	bool might_overlap;

	if (ptq->stop) {
		b->len = 0;
		return 0;
	}

	queue = &ptq->pt->queues.queue_array[ptq->queue_nr];

	buffer = auxtrace_buffer__next(queue, buffer);
	if (!buffer) {
		if (old_buffer)
			auxtrace_buffer__drop_data(old_buffer);
		b->len = 0;
		return 0;
	}

	ptq->buffer = buffer;

	if (!buffer->data) {
		int fd = perf_data__fd(ptq->pt->session->data);

		buffer->data = auxtrace_buffer__get_data(buffer, fd);
		if (!buffer->data)
			return -ENOMEM;
	}

	might_overlap = ptq->pt->snapshot_mode || ptq->pt->sampling_mode;
	if (might_overlap && !buffer->consecutive && old_buffer &&
	    intel_pt_do_fix_overlap(ptq->pt, old_buffer, buffer))
		return -ENOMEM;

	if (buffer->use_data) {
		b->len = buffer->use_size;
		b->buf = buffer->use_data;
	} else {
		b->len = buffer->size;
		b->buf = buffer->data;
	}
	b->ref_timestamp = buffer->reference;

	if (!old_buffer || (might_overlap && !buffer->consecutive)) {
		b->consecutive = false;
		b->trace_nr = buffer->buffer_nr + 1;
	} else {
		b->consecutive = true;
	}

	if (ptq->step_through_buffers)
		ptq->stop = true;

	if (b->len) {
		if (old_buffer)
			auxtrace_buffer__drop_data(old_buffer);
		ptq->old_buffer = buffer;
	} else {
		auxtrace_buffer__drop_data(buffer);
		return intel_pt_get_trace(b, data);
	}

	return 0;
}