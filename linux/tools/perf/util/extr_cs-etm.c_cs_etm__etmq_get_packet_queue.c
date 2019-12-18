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
struct cs_etm_packet_queue {int dummy; } ;
struct cs_etm_traceid_queue {struct cs_etm_packet_queue packet_queue; } ;
struct cs_etm_queue {int dummy; } ;

/* Variables and functions */
 struct cs_etm_traceid_queue* cs_etm__etmq_get_traceid_queue (struct cs_etm_queue*,int /*<<< orphan*/ ) ; 

struct cs_etm_packet_queue
*cs_etm__etmq_get_packet_queue(struct cs_etm_queue *etmq, u8 trace_chan_id)
{
	struct cs_etm_traceid_queue *tidq;

	tidq = cs_etm__etmq_get_traceid_queue(etmq, trace_chan_id);
	if (tidq)
		return &tidq->packet_queue;

	return NULL;
}