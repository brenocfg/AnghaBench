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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_queue {scalar_t__ pending_timestamp; } ;
struct cs_etm_packet_queue {int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 struct cs_etm_packet_queue* cs_etm__etmq_get_packet_queue (struct cs_etm_queue*,scalar_t__) ; 

__attribute__((used)) static u64 cs_etm__etmq_get_timestamp(struct cs_etm_queue *etmq,
				      u8 *trace_chan_id)
{
	struct cs_etm_packet_queue *packet_queue;

	if (!etmq->pending_timestamp)
		return 0;

	if (trace_chan_id)
		*trace_chan_id = etmq->pending_timestamp;

	packet_queue = cs_etm__etmq_get_packet_queue(etmq,
						     etmq->pending_timestamp);
	if (!packet_queue)
		return 0;

	/* Acknowledge pending status */
	etmq->pending_timestamp = 0;

	/* See function cs_etm_decoder__do_{hard|soft}_timestamp() */
	return packet_queue->timestamp;
}