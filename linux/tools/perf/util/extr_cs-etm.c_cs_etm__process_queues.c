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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_traceid_queue {int dummy; } ;
struct cs_etm_queue {int dummy; } ;
struct TYPE_7__ {TYPE_1__* heap_array; int /*<<< orphan*/  heap_cnt; } ;
struct TYPE_6__ {struct auxtrace_queue* queue_array; } ;
struct cs_etm_auxtrace {TYPE_3__ heap; TYPE_2__ queues; } ;
struct auxtrace_queue {struct cs_etm_queue* priv; } ;
struct TYPE_5__ {unsigned int queue_nr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TO_CS_QUEUE_NR (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int TO_QUEUE_NR (unsigned int) ; 
 int /*<<< orphan*/  TO_TRACE_CHAN_ID (unsigned int) ; 
 int auxtrace_heap__add (TYPE_3__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auxtrace_heap__pop (TYPE_3__*) ; 
 int /*<<< orphan*/  cs_etm__clear_all_traceid_queues (struct cs_etm_queue*) ; 
 int cs_etm__decode_data_block (struct cs_etm_queue*) ; 
 int /*<<< orphan*/  cs_etm__etmq_get_timestamp (struct cs_etm_queue*,int /*<<< orphan*/ *) ; 
 struct cs_etm_traceid_queue* cs_etm__etmq_get_traceid_queue (struct cs_etm_queue*,int /*<<< orphan*/ ) ; 
 int cs_etm__get_data_block (struct cs_etm_queue*) ; 
 int cs_etm__process_traceid_queue (struct cs_etm_queue*,struct cs_etm_traceid_queue*) ; 

__attribute__((used)) static int cs_etm__process_queues(struct cs_etm_auxtrace *etm)
{
	int ret = 0;
	unsigned int cs_queue_nr, queue_nr;
	u8 trace_chan_id;
	u64 timestamp;
	struct auxtrace_queue *queue;
	struct cs_etm_queue *etmq;
	struct cs_etm_traceid_queue *tidq;

	while (1) {
		if (!etm->heap.heap_cnt)
			goto out;

		/* Take the entry at the top of the min heap */
		cs_queue_nr = etm->heap.heap_array[0].queue_nr;
		queue_nr = TO_QUEUE_NR(cs_queue_nr);
		trace_chan_id = TO_TRACE_CHAN_ID(cs_queue_nr);
		queue = &etm->queues.queue_array[queue_nr];
		etmq = queue->priv;

		/*
		 * Remove the top entry from the heap since we are about
		 * to process it.
		 */
		auxtrace_heap__pop(&etm->heap);

		tidq  = cs_etm__etmq_get_traceid_queue(etmq, trace_chan_id);
		if (!tidq) {
			/*
			 * No traceID queue has been allocated for this traceID,
			 * which means something somewhere went very wrong.  No
			 * other choice than simply exit.
			 */
			ret = -EINVAL;
			goto out;
		}

		/*
		 * Packets associated with this timestamp are already in
		 * the etmq's traceID queue, so process them.
		 */
		ret = cs_etm__process_traceid_queue(etmq, tidq);
		if (ret < 0)
			goto out;

		/*
		 * Packets for this timestamp have been processed, time to
		 * move on to the next timestamp, fetching a new auxtrace_buffer
		 * if need be.
		 */
refetch:
		ret = cs_etm__get_data_block(etmq);
		if (ret < 0)
			goto out;

		/*
		 * No more auxtrace_buffers to process in this etmq, simply
		 * move on to another entry in the auxtrace_heap.
		 */
		if (!ret)
			continue;

		ret = cs_etm__decode_data_block(etmq);
		if (ret)
			goto out;

		timestamp = cs_etm__etmq_get_timestamp(etmq, &trace_chan_id);

		if (!timestamp) {
			/*
			 * Function cs_etm__decode_data_block() returns when
			 * there is no more traces to decode in the current
			 * auxtrace_buffer OR when a timestamp has been
			 * encountered on any of the traceID queues.  Since we
			 * did not get a timestamp, there is no more traces to
			 * process in this auxtrace_buffer.  As such empty and
			 * flush all traceID queues.
			 */
			cs_etm__clear_all_traceid_queues(etmq);

			/* Fetch another auxtrace_buffer for this etmq */
			goto refetch;
		}

		/*
		 * Add to the min heap the timestamp for packets that have
		 * just been decoded.  They will be processed and synthesized
		 * during the next call to cs_etm__process_traceid_queue() for
		 * this queue/traceID.
		 */
		cs_queue_nr = TO_CS_QUEUE_NR(queue_nr, trace_chan_id);
		ret = auxtrace_heap__add(&etm->heap, cs_queue_nr, timestamp);
	}

out:
	return ret;
}