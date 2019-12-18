#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ state; int /*<<< orphan*/  cpu; int /*<<< orphan*/  kthread; int /*<<< orphan*/  pc; } ;
typedef  TYPE_2__ kd_stc_64 ;
struct TYPE_11__ {scalar_t__ data; } ;
typedef  TYPE_3__ kd_packet_t ;
struct TYPE_9__ {scalar_t__ signum; void* type; int /*<<< orphan*/  tid; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {TYPE_1__ reason; } ;
typedef  void* RDebugReasonType ;
typedef  TYPE_4__ RDebug ;

/* Variables and functions */
 scalar_t__ DbgKdExceptionStateChange ; 
 scalar_t__ DbgKdLoadSymbolsStateChange ; 
 int KD_E_OK ; 
 int /*<<< orphan*/  KD_PACKET_TYPE_STATE_CHANGE64 ; 
 void* R_DEBUG_REASON_ERROR ; 
 void* R_DEBUG_REASON_INT ; 
 void* R_DEBUG_REASON_NEW_LIB ; 
 void* R_DEBUG_REASON_UNKNOWN ; 
 int /*<<< orphan*/  R_FREE (TYPE_3__*) ; 
 int dbreak ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  wctx ; 
 int /*<<< orphan*/  windbg_break (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windbg_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int windbg_wait_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 

__attribute__((used)) static RDebugReasonType r_debug_windbg_wait(RDebug *dbg, int pid) {
	RDebugReasonType reason = R_DEBUG_REASON_UNKNOWN;
	kd_packet_t *pkt = NULL;
	kd_stc_64 *stc;
	dbreak = false;

	for (;;) {
		int ret = windbg_wait_packet (wctx, KD_PACKET_TYPE_STATE_CHANGE64, &pkt);
		if (dbreak) {
			dbreak = false;
			windbg_break (wctx);
			R_FREE (pkt);
			continue;
		}
		if (ret != KD_E_OK || !pkt) {
			reason = R_DEBUG_REASON_ERROR;
			break;
		}
		stc = (kd_stc_64 *) pkt->data;
		dbg->reason.addr = stc->pc;
		dbg->reason.tid = stc->kthread;
		dbg->reason.signum = stc->state;
		windbg_set_cpu (wctx, stc->cpu);
		if (stc->state == DbgKdExceptionStateChange) {
			dbg->reason.type = R_DEBUG_REASON_INT;
			reason = R_DEBUG_REASON_INT;
			break;
		} else if (stc->state == DbgKdLoadSymbolsStateChange) {
			dbg->reason.type = R_DEBUG_REASON_NEW_LIB;
			reason = R_DEBUG_REASON_NEW_LIB;
			break;
		}
		R_FREE (pkt);
	}
	free (pkt);
	return reason;
}