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
struct cs_etm_packet {int last_instr_taken_branch; int /*<<< orphan*/  end_addr; int /*<<< orphan*/  start_addr; } ;
struct cs_etm_decoder {size_t tail; struct cs_etm_packet* packet_buffer; } ;
struct TYPE_3__ {int last_i_type; int last_instr_exec; int /*<<< orphan*/  en_addr; int /*<<< orphan*/  st_addr; } ;
typedef  TYPE_1__ ocsd_generic_trace_elem ;
typedef  int ocsd_datapath_resp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ETM_RANGE ; 
#define  OCSD_INSTR_BR 132 
#define  OCSD_INSTR_BR_INDIRECT 131 
#define  OCSD_INSTR_DSB_DMB 130 
#define  OCSD_INSTR_ISB 129 
#define  OCSD_INSTR_OTHER 128 
 int OCSD_RESP_CONT ; 
 int OCSD_RESP_WAIT ; 
 int cs_etm_decoder__buffer_packet (struct cs_etm_decoder*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__buffer_range(struct cs_etm_decoder *decoder,
			     const ocsd_generic_trace_elem *elem,
			     const uint8_t trace_chan_id)
{
	int ret = 0;
	struct cs_etm_packet *packet;

	ret = cs_etm_decoder__buffer_packet(decoder, trace_chan_id,
					    CS_ETM_RANGE);
	if (ret != OCSD_RESP_CONT && ret != OCSD_RESP_WAIT)
		return ret;

	packet = &decoder->packet_buffer[decoder->tail];

	packet->start_addr = elem->st_addr;
	packet->end_addr = elem->en_addr;
	switch (elem->last_i_type) {
	case OCSD_INSTR_BR:
	case OCSD_INSTR_BR_INDIRECT:
		packet->last_instr_taken_branch = elem->last_instr_exec;
		break;
	case OCSD_INSTR_ISB:
	case OCSD_INSTR_DSB_DMB:
	case OCSD_INSTR_OTHER:
	default:
		packet->last_instr_taken_branch = false;
		break;
	}

	return ret;
}