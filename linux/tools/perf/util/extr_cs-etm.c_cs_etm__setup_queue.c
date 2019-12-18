#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_queue {unsigned int queue_nr; scalar_t__ offset; struct cs_etm_auxtrace* etm; } ;
struct cs_etm_auxtrace {int /*<<< orphan*/  heap; scalar_t__ timeless_decoding; } ;
struct auxtrace_queue {struct cs_etm_queue* priv; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int TO_CS_QUEUE_NR (unsigned int,int /*<<< orphan*/ ) ; 
 int auxtrace_heap__add (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 struct cs_etm_queue* cs_etm__alloc_queue (struct cs_etm_auxtrace*) ; 
 int /*<<< orphan*/  cs_etm__clear_all_packet_queues (struct cs_etm_queue*) ; 
 int cs_etm__decode_data_block (struct cs_etm_queue*) ; 
 int /*<<< orphan*/  cs_etm__etmq_get_timestamp (struct cs_etm_queue*,int /*<<< orphan*/ *) ; 
 int cs_etm__get_data_block (struct cs_etm_queue*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_id_chan ; 

__attribute__((used)) static int cs_etm__setup_queue(struct cs_etm_auxtrace *etm,
			       struct auxtrace_queue *queue,
			       unsigned int queue_nr)
{
	int ret = 0;
	unsigned int cs_queue_nr;
	u8 trace_chan_id;
	u64 timestamp;
	struct cs_etm_queue *etmq = queue->priv;

	if (list_empty(&queue->head) || etmq)
		goto out;

	etmq = cs_etm__alloc_queue(etm);

	if (!etmq) {
		ret = -ENOMEM;
		goto out;
	}

	queue->priv = etmq;
	etmq->etm = etm;
	etmq->queue_nr = queue_nr;
	etmq->offset = 0;

	if (etm->timeless_decoding)
		goto out;

	/*
	 * We are under a CPU-wide trace scenario.  As such we need to know
	 * when the code that generated the traces started to execute so that
	 * it can be correlated with execution on other CPUs.  So we get a
	 * handle on the beginning of traces and decode until we find a
	 * timestamp.  The timestamp is then added to the auxtrace min heap
	 * in order to know what nibble (of all the etmqs) to decode first.
	 */
	while (1) {
		/*
		 * Fetch an aux_buffer from this etmq.  Bail if no more
		 * blocks or an error has been encountered.
		 */
		ret = cs_etm__get_data_block(etmq);
		if (ret <= 0)
			goto out;

		/*
		 * Run decoder on the trace block.  The decoder will stop when
		 * encountering a timestamp, a full packet queue or the end of
		 * trace for that block.
		 */
		ret = cs_etm__decode_data_block(etmq);
		if (ret)
			goto out;

		/*
		 * Function cs_etm_decoder__do_{hard|soft}_timestamp() does all
		 * the timestamp calculation for us.
		 */
		timestamp = cs_etm__etmq_get_timestamp(etmq, &trace_chan_id);

		/* We found a timestamp, no need to continue. */
		if (timestamp)
			break;

		/*
		 * We didn't find a timestamp so empty all the traceid packet
		 * queues before looking for another timestamp packet, either
		 * in the current data block or a new one.  Packets that were
		 * just decoded are useless since no timestamp has been
		 * associated with them.  As such simply discard them.
		 */
		cs_etm__clear_all_packet_queues(etmq);
	}

	/*
	 * We have a timestamp.  Add it to the min heap to reflect when
	 * instructions conveyed by the range packets of this traceID queue
	 * started to execute.  Once the same has been done for all the traceID
	 * queues of each etmq, redenring and decoding can start in
	 * chronological order.
	 *
	 * Note that packets decoded above are still in the traceID's packet
	 * queue and will be processed in cs_etm__process_queues().
	 */
	cs_queue_nr = TO_CS_QUEUE_NR(queue_nr, trace_id_chan);
	ret = auxtrace_heap__add(&etm->heap, cs_queue_nr, timestamp);
out:
	return ret;
}