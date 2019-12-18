#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_pt_queue {int stop; size_t queue_nr; struct auxtrace_buffer* old_buffer; scalar_t__ step_through_buffers; struct auxtrace_buffer* buffer; TYPE_2__* pt; } ;
struct intel_pt_buffer {scalar_t__ len; } ;
struct auxtrace_queue {int dummy; } ;
struct auxtrace_buffer {int dummy; } ;
struct TYPE_3__ {struct auxtrace_queue* queue_array; } ;
struct TYPE_4__ {TYPE_1__ queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxtrace_buffer__drop_data (struct auxtrace_buffer*) ; 
 struct auxtrace_buffer* auxtrace_buffer__next (struct auxtrace_queue*,struct auxtrace_buffer*) ; 
 int intel_pt_get_buffer (struct intel_pt_queue*,struct auxtrace_buffer*,struct auxtrace_buffer*,struct intel_pt_buffer*) ; 

__attribute__((used)) static int intel_pt_get_trace(struct intel_pt_buffer *b, void *data)
{
	struct intel_pt_queue *ptq = data;
	struct auxtrace_buffer *buffer = ptq->buffer;
	struct auxtrace_buffer *old_buffer = ptq->old_buffer;
	struct auxtrace_queue *queue;
	int err;

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

	err = intel_pt_get_buffer(ptq, buffer, old_buffer, b);
	if (err)
		return err;

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