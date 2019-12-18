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
typedef  int /*<<< orphan*/  uint8_t ;
struct cs_etm_queue {int dummy; } ;
struct cs_etm_packet_queue {scalar_t__ instr_count; scalar_t__ next_timestamp; scalar_t__ timestamp; } ;
typedef  int /*<<< orphan*/  ocsd_datapath_resp_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCSD_RESP_CONT ; 
 int /*<<< orphan*/  OCSD_RESP_WAIT ; 
 int /*<<< orphan*/  cs_etm__etmq_set_traceid_queue_timestamp (struct cs_etm_queue*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__do_soft_timestamp(struct cs_etm_queue *etmq,
				  struct cs_etm_packet_queue *packet_queue,
				  const uint8_t trace_chan_id)
{
	/* No timestamp packet has been received, nothing to do */
	if (!packet_queue->timestamp)
		return OCSD_RESP_CONT;

	packet_queue->timestamp = packet_queue->next_timestamp;

	/* Estimate the timestamp for the next range packet */
	packet_queue->next_timestamp += packet_queue->instr_count;
	packet_queue->instr_count = 0;

	/* Tell the front end which traceid_queue needs attention */
	cs_etm__etmq_set_traceid_queue_timestamp(etmq, trace_chan_id);

	return OCSD_RESP_WAIT;
}