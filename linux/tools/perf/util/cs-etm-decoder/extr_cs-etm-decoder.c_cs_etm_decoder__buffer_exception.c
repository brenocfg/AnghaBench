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
struct cs_etm_packet_queue {size_t tail; struct cs_etm_packet* packet_buffer; } ;
struct cs_etm_packet {int /*<<< orphan*/  exception_number; } ;
struct TYPE_3__ {int /*<<< orphan*/  exception_number; } ;
typedef  TYPE_1__ ocsd_generic_trace_elem ;
typedef  int ocsd_datapath_resp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ETM_EXCEPTION ; 
 int OCSD_RESP_CONT ; 
 int OCSD_RESP_WAIT ; 
 int cs_etm_decoder__buffer_packet (struct cs_etm_packet_queue*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__buffer_exception(struct cs_etm_packet_queue *queue,
				 const ocsd_generic_trace_elem *elem,
				 const uint8_t trace_chan_id)
{	int ret = 0;
	struct cs_etm_packet *packet;

	ret = cs_etm_decoder__buffer_packet(queue, trace_chan_id,
					    CS_ETM_EXCEPTION);
	if (ret != OCSD_RESP_CONT && ret != OCSD_RESP_WAIT)
		return ret;

	packet = &queue->packet_buffer[queue->tail];
	packet->exception_number = elem->exception_number;

	return ret;
}