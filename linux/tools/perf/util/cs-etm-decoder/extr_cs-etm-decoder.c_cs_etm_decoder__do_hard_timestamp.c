#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct cs_etm_queue {int dummy; } ;
struct cs_etm_packet_queue {scalar_t__ instr_count; scalar_t__ next_timestamp; scalar_t__ timestamp; } ;
struct TYPE_3__ {scalar_t__ timestamp; } ;
typedef  TYPE_1__ ocsd_generic_trace_elem ;
typedef  int /*<<< orphan*/  ocsd_datapath_resp_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCSD_RESP_CONT ; 
 int /*<<< orphan*/  OCSD_RESP_FATAL_SYS_ERR ; 
 int /*<<< orphan*/  OCSD_RESP_WAIT ; 
 struct cs_etm_packet_queue* cs_etm__etmq_get_packet_queue (struct cs_etm_queue*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cs_etm__etmq_set_traceid_queue_timestamp (struct cs_etm_queue*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__do_hard_timestamp(struct cs_etm_queue *etmq,
				  const ocsd_generic_trace_elem *elem,
				  const uint8_t trace_chan_id)
{
	struct cs_etm_packet_queue *packet_queue;

	/* First get the packet queue for this traceID */
	packet_queue = cs_etm__etmq_get_packet_queue(etmq, trace_chan_id);
	if (!packet_queue)
		return OCSD_RESP_FATAL_SYS_ERR;

	/*
	 * We've seen a timestamp packet before - simply record the new value.
	 * Function do_soft_timestamp() will report the value to the front end,
	 * hence asking the decoder to keep decoding rather than stopping.
	 */
	if (packet_queue->timestamp) {
		packet_queue->next_timestamp = elem->timestamp;
		return OCSD_RESP_CONT;
	}

	/*
	 * This is the first timestamp we've seen since the beginning of traces
	 * or a discontinuity.  Since timestamps packets are generated *after*
	 * range packets have been generated, we need to estimate the time at
	 * which instructions started by substracting the number of instructions
	 * executed to the timestamp.
	 */
	packet_queue->timestamp = elem->timestamp - packet_queue->instr_count;
	packet_queue->next_timestamp = elem->timestamp;
	packet_queue->instr_count = 0;

	/* Tell the front end which traceid_queue needs attention */
	cs_etm__etmq_set_traceid_queue_timestamp(etmq, trace_chan_id);

	/* Halt processing until we are being told to proceed */
	return OCSD_RESP_WAIT;
}