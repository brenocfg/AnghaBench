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
struct intel_pt_queue {size_t queue_nr; TYPE_2__* pt; struct auxtrace_buffer* old_buffer; struct auxtrace_buffer* buffer; } ;
struct intel_pt_buffer {scalar_t__ len; } ;
struct auxtrace_queue {int dummy; } ;
struct auxtrace_buffer {int dummy; } ;
typedef  int (* intel_pt_lookahead_cb_t ) (struct intel_pt_buffer*,void*) ;
struct TYPE_3__ {struct auxtrace_queue* queue_array; } ;
struct TYPE_4__ {TYPE_1__ queues; } ;

/* Variables and functions */
 struct auxtrace_buffer* auxtrace_buffer__next (struct auxtrace_queue*,struct auxtrace_buffer*) ; 
 int intel_pt_get_buffer (struct intel_pt_queue*,struct auxtrace_buffer*,struct auxtrace_buffer*,struct intel_pt_buffer*) ; 
 int /*<<< orphan*/  intel_pt_lookahead_drop_buffer (struct intel_pt_queue*,struct auxtrace_buffer*) ; 

__attribute__((used)) static int intel_pt_lookahead(void *data, intel_pt_lookahead_cb_t cb,
			      void *cb_data)
{
	struct intel_pt_queue *ptq = data;
	struct auxtrace_buffer *buffer = ptq->buffer;
	struct auxtrace_buffer *old_buffer = ptq->old_buffer;
	struct auxtrace_queue *queue;
	int err = 0;

	queue = &ptq->pt->queues.queue_array[ptq->queue_nr];

	while (1) {
		struct intel_pt_buffer b = { .len = 0 };

		buffer = auxtrace_buffer__next(queue, buffer);
		if (!buffer)
			break;

		err = intel_pt_get_buffer(ptq, buffer, old_buffer, &b);
		if (err)
			break;

		if (b.len) {
			intel_pt_lookahead_drop_buffer(ptq, old_buffer);
			old_buffer = buffer;
		} else {
			intel_pt_lookahead_drop_buffer(ptq, buffer);
			continue;
		}

		err = cb(&b, cb_data);
		if (err)
			break;
	}

	if (buffer != old_buffer)
		intel_pt_lookahead_drop_buffer(ptq, buffer);
	intel_pt_lookahead_drop_buffer(ptq, old_buffer);

	return err;
}