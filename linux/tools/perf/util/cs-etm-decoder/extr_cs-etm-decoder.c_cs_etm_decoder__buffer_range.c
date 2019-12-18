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
struct cs_etm_packet_queue {size_t tail; int /*<<< orphan*/  instr_count; struct cs_etm_packet* packet_buffer; } ;
struct cs_etm_packet {int last_instr_type; int last_instr_taken_branch; int /*<<< orphan*/  last_instr_size; int /*<<< orphan*/  last_instr_cond; int /*<<< orphan*/  last_instr_subtype; scalar_t__ instr_count; int /*<<< orphan*/  end_addr; int /*<<< orphan*/  start_addr; int /*<<< orphan*/  isa; } ;
struct TYPE_3__ {int isa; int last_i_type; int last_instr_exec; scalar_t__ num_instr_range; int /*<<< orphan*/  last_instr_sz; int /*<<< orphan*/  last_instr_cond; int /*<<< orphan*/  last_i_subtype; int /*<<< orphan*/  en_addr; int /*<<< orphan*/  st_addr; } ;
typedef  TYPE_1__ ocsd_generic_trace_elem ;
typedef  int ocsd_datapath_resp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ETM_ISA_A32 ; 
 int /*<<< orphan*/  CS_ETM_ISA_A64 ; 
 int /*<<< orphan*/  CS_ETM_ISA_T32 ; 
 int /*<<< orphan*/  CS_ETM_ISA_UNKNOWN ; 
 int /*<<< orphan*/  CS_ETM_RANGE ; 
#define  OCSD_INSTR_BR 140 
#define  OCSD_INSTR_BR_INDIRECT 139 
#define  OCSD_INSTR_DSB_DMB 138 
#define  OCSD_INSTR_ISB 137 
#define  OCSD_INSTR_OTHER 136 
#define  OCSD_INSTR_WFI_WFE 135 
 int OCSD_RESP_CONT ; 
 int OCSD_RESP_WAIT ; 
 scalar_t__ cs_etm__etmq_is_timeless (struct cs_etm_queue*) ; 
 int cs_etm_decoder__buffer_packet (struct cs_etm_packet_queue*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int cs_etm_decoder__do_soft_timestamp (struct cs_etm_queue*,struct cs_etm_packet_queue*,int /*<<< orphan*/  const) ; 
#define  ocsd_isa_aarch64 134 
#define  ocsd_isa_arm 133 
#define  ocsd_isa_custom 132 
#define  ocsd_isa_jazelle 131 
#define  ocsd_isa_tee 130 
#define  ocsd_isa_thumb2 129 
#define  ocsd_isa_unknown 128 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__buffer_range(struct cs_etm_queue *etmq,
			     struct cs_etm_packet_queue *packet_queue,
			     const ocsd_generic_trace_elem *elem,
			     const uint8_t trace_chan_id)
{
	int ret = 0;
	struct cs_etm_packet *packet;

	ret = cs_etm_decoder__buffer_packet(packet_queue, trace_chan_id,
					    CS_ETM_RANGE);
	if (ret != OCSD_RESP_CONT && ret != OCSD_RESP_WAIT)
		return ret;

	packet = &packet_queue->packet_buffer[packet_queue->tail];

	switch (elem->isa) {
	case ocsd_isa_aarch64:
		packet->isa = CS_ETM_ISA_A64;
		break;
	case ocsd_isa_arm:
		packet->isa = CS_ETM_ISA_A32;
		break;
	case ocsd_isa_thumb2:
		packet->isa = CS_ETM_ISA_T32;
		break;
	case ocsd_isa_tee:
	case ocsd_isa_jazelle:
	case ocsd_isa_custom:
	case ocsd_isa_unknown:
	default:
		packet->isa = CS_ETM_ISA_UNKNOWN;
	}

	packet->start_addr = elem->st_addr;
	packet->end_addr = elem->en_addr;
	packet->instr_count = elem->num_instr_range;
	packet->last_instr_type = elem->last_i_type;
	packet->last_instr_subtype = elem->last_i_subtype;
	packet->last_instr_cond = elem->last_instr_cond;

	switch (elem->last_i_type) {
	case OCSD_INSTR_BR:
	case OCSD_INSTR_BR_INDIRECT:
		packet->last_instr_taken_branch = elem->last_instr_exec;
		break;
	case OCSD_INSTR_ISB:
	case OCSD_INSTR_DSB_DMB:
	case OCSD_INSTR_WFI_WFE:
	case OCSD_INSTR_OTHER:
	default:
		packet->last_instr_taken_branch = false;
		break;
	}

	packet->last_instr_size = elem->last_instr_sz;

	/* per-thread scenario, no need to generate a timestamp */
	if (cs_etm__etmq_is_timeless(etmq))
		goto out;

	/*
	 * The packet queue is full and we haven't seen a timestamp (had we
	 * seen one the packet queue wouldn't be full).  Let the front end
	 * deal with it.
	 */
	if (ret == OCSD_RESP_WAIT)
		goto out;

	packet_queue->instr_count += elem->num_instr_range;
	/* Tell the front end we have a new timestamp to process */
	ret = cs_etm_decoder__do_soft_timestamp(etmq, packet_queue,
						trace_chan_id);
out:
	return ret;
}