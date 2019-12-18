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
struct cs_etm_packet_queue {int packet_count; int tail; TYPE_1__* packet_buffer; } ;
typedef  int /*<<< orphan*/  ocsd_datapath_resp_t ;
typedef  enum cs_etm_sample_type { ____Placeholder_cs_etm_sample_type } cs_etm_sample_type ;
struct TYPE_2__ {int sample_type; int cpu; int last_instr_taken_branch; int /*<<< orphan*/  trace_chan_id; int /*<<< orphan*/  exception_number; scalar_t__ flags; scalar_t__ last_instr_cond; scalar_t__ last_instr_subtype; scalar_t__ last_instr_type; scalar_t__ last_instr_size; scalar_t__ instr_count; void* end_addr; void* start_addr; int /*<<< orphan*/  isa; } ;

/* Variables and functions */
 void* CS_ETM_INVAL_ADDR ; 
 int /*<<< orphan*/  CS_ETM_ISA_UNKNOWN ; 
 int CS_ETM_PACKET_MAX_BUFFER ; 
 int /*<<< orphan*/  OCSD_RESP_CONT ; 
 int /*<<< orphan*/  OCSD_RESP_FATAL_SYS_ERR ; 
 int /*<<< orphan*/  OCSD_RESP_WAIT ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 scalar_t__ cs_etm__get_cpu (int /*<<< orphan*/  const,int*) ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__buffer_packet(struct cs_etm_packet_queue *packet_queue,
			      const u8 trace_chan_id,
			      enum cs_etm_sample_type sample_type)
{
	u32 et = 0;
	int cpu;

	if (packet_queue->packet_count >= CS_ETM_PACKET_MAX_BUFFER - 1)
		return OCSD_RESP_FATAL_SYS_ERR;

	if (cs_etm__get_cpu(trace_chan_id, &cpu) < 0)
		return OCSD_RESP_FATAL_SYS_ERR;

	et = packet_queue->tail;
	et = (et + 1) & (CS_ETM_PACKET_MAX_BUFFER - 1);
	packet_queue->tail = et;
	packet_queue->packet_count++;

	packet_queue->packet_buffer[et].sample_type = sample_type;
	packet_queue->packet_buffer[et].isa = CS_ETM_ISA_UNKNOWN;
	packet_queue->packet_buffer[et].cpu = cpu;
	packet_queue->packet_buffer[et].start_addr = CS_ETM_INVAL_ADDR;
	packet_queue->packet_buffer[et].end_addr = CS_ETM_INVAL_ADDR;
	packet_queue->packet_buffer[et].instr_count = 0;
	packet_queue->packet_buffer[et].last_instr_taken_branch = false;
	packet_queue->packet_buffer[et].last_instr_size = 0;
	packet_queue->packet_buffer[et].last_instr_type = 0;
	packet_queue->packet_buffer[et].last_instr_subtype = 0;
	packet_queue->packet_buffer[et].last_instr_cond = 0;
	packet_queue->packet_buffer[et].flags = 0;
	packet_queue->packet_buffer[et].exception_number = UINT32_MAX;
	packet_queue->packet_buffer[et].trace_chan_id = trace_chan_id;

	if (packet_queue->packet_count == CS_ETM_PACKET_MAX_BUFFER - 1)
		return OCSD_RESP_WAIT;

	return OCSD_RESP_CONT;
}