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
typedef  scalar_t__ u64 ;
struct cs_etm_traceid_queue {struct cs_etm_packet* prev_packet; struct cs_etm_packet* packet; int /*<<< orphan*/  trace_chan_id; } ;
struct cs_etm_queue {int dummy; } ;
struct cs_etm_packet {scalar_t__ exception_number; int /*<<< orphan*/  end_addr; } ;

/* Variables and functions */
 scalar_t__ CS_ETMV3_EXC_SVC ; 
 scalar_t__ CS_ETMV4_EXC_CALL ; 
 scalar_t__ __perf_cs_etmv3_magic ; 
 scalar_t__ __perf_cs_etmv4_magic ; 
 scalar_t__ cs_etm__is_svc_instr (struct cs_etm_queue*,int /*<<< orphan*/ ,struct cs_etm_packet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cs_etm__is_syscall(struct cs_etm_queue *etmq,
			       struct cs_etm_traceid_queue *tidq, u64 magic)
{
	u8 trace_chan_id = tidq->trace_chan_id;
	struct cs_etm_packet *packet = tidq->packet;
	struct cs_etm_packet *prev_packet = tidq->prev_packet;

	if (magic == __perf_cs_etmv3_magic)
		if (packet->exception_number == CS_ETMV3_EXC_SVC)
			return true;

	/*
	 * ETMv4 exception type CS_ETMV4_EXC_CALL covers SVC, SMC and
	 * HVC cases; need to check if it's SVC instruction based on
	 * packet address.
	 */
	if (magic == __perf_cs_etmv4_magic) {
		if (packet->exception_number == CS_ETMV4_EXC_CALL &&
		    cs_etm__is_svc_instr(etmq, trace_chan_id, prev_packet,
					 prev_packet->end_addr))
			return true;
	}

	return false;
}