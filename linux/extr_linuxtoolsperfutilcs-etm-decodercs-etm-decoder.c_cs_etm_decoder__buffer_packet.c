#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct int_node {scalar_t__ priv; } ;
struct cs_etm_decoder {int packet_count; int tail; TYPE_1__* packet_buffer; } ;
typedef  int /*<<< orphan*/  ocsd_datapath_resp_t ;
typedef  enum cs_etm_sample_type { ____Placeholder_cs_etm_sample_type } cs_etm_sample_type ;
struct TYPE_2__ {int sample_type; int exc; int exc_ret; int cpu; void* end_addr; void* start_addr; } ;

/* Variables and functions */
 void* CS_ETM_INVAL_ADDR ; 
 int MAX_BUFFER ; 
 int /*<<< orphan*/  OCSD_RESP_CONT ; 
 int /*<<< orphan*/  OCSD_RESP_FATAL_SYS_ERR ; 
 int /*<<< orphan*/  OCSD_RESP_WAIT ; 
 struct int_node* intlist__find (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  traceid_list ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__buffer_packet(struct cs_etm_decoder *decoder,
			      const u8 trace_chan_id,
			      enum cs_etm_sample_type sample_type)
{
	u32 et = 0;
	struct int_node *inode = NULL;

	if (decoder->packet_count >= MAX_BUFFER - 1)
		return OCSD_RESP_FATAL_SYS_ERR;

	/* Search the RB tree for the cpu associated with this traceID */
	inode = intlist__find(traceid_list, trace_chan_id);
	if (!inode)
		return OCSD_RESP_FATAL_SYS_ERR;

	et = decoder->tail;
	et = (et + 1) & (MAX_BUFFER - 1);
	decoder->tail = et;
	decoder->packet_count++;

	decoder->packet_buffer[et].sample_type = sample_type;
	decoder->packet_buffer[et].exc = false;
	decoder->packet_buffer[et].exc_ret = false;
	decoder->packet_buffer[et].cpu = *((int *)inode->priv);
	decoder->packet_buffer[et].start_addr = CS_ETM_INVAL_ADDR;
	decoder->packet_buffer[et].end_addr = CS_ETM_INVAL_ADDR;

	if (decoder->packet_count == MAX_BUFFER - 1)
		return OCSD_RESP_WAIT;

	return OCSD_RESP_CONT;
}