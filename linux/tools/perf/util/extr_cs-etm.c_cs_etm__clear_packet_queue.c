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
struct cs_etm_packet_queue {TYPE_1__* packet_buffer; scalar_t__ packet_count; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_2__ {int last_instr_taken_branch; int /*<<< orphan*/  cpu; int /*<<< orphan*/  trace_chan_id; int /*<<< orphan*/  exception_number; scalar_t__ flags; scalar_t__ last_instr_cond; scalar_t__ last_instr_subtype; scalar_t__ last_instr_type; scalar_t__ last_instr_size; scalar_t__ instr_count; void* end_addr; void* start_addr; int /*<<< orphan*/  isa; } ;

/* Variables and functions */
 void* CS_ETM_INVAL_ADDR ; 
 int /*<<< orphan*/  CS_ETM_ISA_UNKNOWN ; 
 int CS_ETM_PACKET_MAX_BUFFER ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  UINT8_MAX ; 

__attribute__((used)) static void cs_etm__clear_packet_queue(struct cs_etm_packet_queue *queue)
{
	int i;

	queue->head = 0;
	queue->tail = 0;
	queue->packet_count = 0;
	for (i = 0; i < CS_ETM_PACKET_MAX_BUFFER; i++) {
		queue->packet_buffer[i].isa = CS_ETM_ISA_UNKNOWN;
		queue->packet_buffer[i].start_addr = CS_ETM_INVAL_ADDR;
		queue->packet_buffer[i].end_addr = CS_ETM_INVAL_ADDR;
		queue->packet_buffer[i].instr_count = 0;
		queue->packet_buffer[i].last_instr_taken_branch = false;
		queue->packet_buffer[i].last_instr_size = 0;
		queue->packet_buffer[i].last_instr_type = 0;
		queue->packet_buffer[i].last_instr_subtype = 0;
		queue->packet_buffer[i].last_instr_cond = 0;
		queue->packet_buffer[i].flags = 0;
		queue->packet_buffer[i].exception_number = UINT32_MAX;
		queue->packet_buffer[i].trace_chan_id = UINT8_MAX;
		queue->packet_buffer[i].cpu = INT_MIN;
	}
}