#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct cs_etm_queue {int dummy; } ;
struct cs_etm_packet_queue {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  context_id; int /*<<< orphan*/  ctxt_id_valid; } ;
struct TYPE_5__ {TYPE_1__ context; } ;
typedef  TYPE_2__ ocsd_generic_trace_elem ;
typedef  int /*<<< orphan*/  ocsd_datapath_resp_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCSD_RESP_CONT ; 
 int /*<<< orphan*/  OCSD_RESP_FATAL_SYS_ERR ; 
 scalar_t__ cs_etm__etmq_set_tid (struct cs_etm_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cs_etm_decoder__reset_timestamp (struct cs_etm_packet_queue*) ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__set_tid(struct cs_etm_queue *etmq,
			struct cs_etm_packet_queue *packet_queue,
			const ocsd_generic_trace_elem *elem,
			const uint8_t trace_chan_id)
{
	pid_t tid;

	/* Ignore PE_CONTEXT packets that don't have a valid contextID */
	if (!elem->context.ctxt_id_valid)
		return OCSD_RESP_CONT;

	tid =  elem->context.context_id;
	if (cs_etm__etmq_set_tid(etmq, tid, trace_chan_id))
		return OCSD_RESP_FATAL_SYS_ERR;

	/*
	 * A timestamp is generated after a PE_CONTEXT element so make sure
	 * to rely on that coming one.
	 */
	cs_etm_decoder__reset_timestamp(packet_queue);

	return OCSD_RESP_CONT;
}