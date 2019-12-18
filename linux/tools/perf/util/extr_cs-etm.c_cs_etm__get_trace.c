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
struct cs_etm_queue {size_t queue_nr; int buf_len; scalar_t__ buf; scalar_t__ buf_used; TYPE_3__* etm; struct auxtrace_buffer* buffer; } ;
struct auxtrace_queue {int dummy; } ;
struct auxtrace_buffer {int size; scalar_t__ data; } ;
struct TYPE_4__ {struct auxtrace_queue* queue_array; } ;
struct TYPE_6__ {TYPE_2__* session; TYPE_1__ queues; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  auxtrace_buffer__drop_data (struct auxtrace_buffer*) ; 
 scalar_t__ auxtrace_buffer__get_data (struct auxtrace_buffer*,int) ; 
 struct auxtrace_buffer* auxtrace_buffer__next (struct auxtrace_queue*,struct auxtrace_buffer*) ; 
 int perf_data__fd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs_etm__get_trace(struct cs_etm_queue *etmq)
{
	struct auxtrace_buffer *aux_buffer = etmq->buffer;
	struct auxtrace_buffer *old_buffer = aux_buffer;
	struct auxtrace_queue *queue;

	queue = &etmq->etm->queues.queue_array[etmq->queue_nr];

	aux_buffer = auxtrace_buffer__next(queue, aux_buffer);

	/* If no more data, drop the previous auxtrace_buffer and return */
	if (!aux_buffer) {
		if (old_buffer)
			auxtrace_buffer__drop_data(old_buffer);
		etmq->buf_len = 0;
		return 0;
	}

	etmq->buffer = aux_buffer;

	/* If the aux_buffer doesn't have data associated, try to load it */
	if (!aux_buffer->data) {
		/* get the file desc associated with the perf data file */
		int fd = perf_data__fd(etmq->etm->session->data);

		aux_buffer->data = auxtrace_buffer__get_data(aux_buffer, fd);
		if (!aux_buffer->data)
			return -ENOMEM;
	}

	/* If valid, drop the previous buffer */
	if (old_buffer)
		auxtrace_buffer__drop_data(old_buffer);

	etmq->buf_used = 0;
	etmq->buf_len = aux_buffer->size;
	etmq->buf = aux_buffer->data;

	return etmq->buf_len;
}