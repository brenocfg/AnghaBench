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
struct intel_pt_queue {TYPE_2__* pt; } ;
struct intel_pt_buffer {int consecutive; scalar_t__ trace_nr; int /*<<< orphan*/  ref_timestamp; scalar_t__ buf; int /*<<< orphan*/  len; } ;
struct auxtrace_buffer {scalar_t__ buffer_nr; int /*<<< orphan*/  consecutive; int /*<<< orphan*/  reference; scalar_t__ data; int /*<<< orphan*/  size; scalar_t__ use_data; int /*<<< orphan*/  use_size; } ;
struct TYPE_4__ {scalar_t__ sampling_mode; scalar_t__ snapshot_mode; TYPE_1__* session; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ auxtrace_buffer__get_data (struct auxtrace_buffer*,int) ; 
 scalar_t__ intel_pt_do_fix_overlap (TYPE_2__*,struct auxtrace_buffer*,struct auxtrace_buffer*) ; 
 int perf_data__fd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_get_buffer(struct intel_pt_queue *ptq,
			       struct auxtrace_buffer *buffer,
			       struct auxtrace_buffer *old_buffer,
			       struct intel_pt_buffer *b)
{
	bool might_overlap;

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

	return 0;
}