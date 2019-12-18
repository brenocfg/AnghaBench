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
struct cs_etm_queue {int /*<<< orphan*/  pending_timestamp; } ;

/* Variables and functions */

void cs_etm__etmq_set_traceid_queue_timestamp(struct cs_etm_queue *etmq,
					      u8 trace_chan_id)
{
	/*
	 * Wnen a timestamp packet is encountered the backend code
	 * is stopped so that the front end has time to process packets
	 * that were accumulated in the traceID queue.  Since there can
	 * be more than one channel per cs_etm_queue, we need to specify
	 * what traceID queue needs servicing.
	 */
	etmq->pending_timestamp = trace_chan_id;
}