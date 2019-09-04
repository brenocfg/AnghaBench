#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ tid; scalar_t__ pid; scalar_t__ present; } ;
struct TYPE_12__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  signum; TYPE_1__ thread; int /*<<< orphan*/  is_valid; } ;
struct TYPE_14__ {scalar_t__ pid; scalar_t__ tid; TYPE_3__ stop_reason; } ;
struct TYPE_11__ {scalar_t__ tid; int /*<<< orphan*/  type; int /*<<< orphan*/  signum; } ;
struct TYPE_13__ {scalar_t__ pid; scalar_t__ tid; TYPE_2__ reason; } ;
typedef  int /*<<< orphan*/  RDebugReasonType ;
typedef  TYPE_4__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  R_DEBUG_REASON_UNKNOWN ; 
 int /*<<< orphan*/  check_connection (TYPE_4__*) ; 
 TYPE_6__* desc ; 
 int /*<<< orphan*/  gdbr_select (TYPE_6__*,scalar_t__,scalar_t__) ; 
 scalar_t__ gdbr_stop_reason (TYPE_6__*) ; 

__attribute__((used)) static RDebugReasonType r_debug_gdb_wait(RDebug *dbg, int pid) {
	check_connection (dbg);
	if (!desc) {
		return R_DEBUG_REASON_UNKNOWN;
	}
	if (!desc->stop_reason.is_valid) {
		if (gdbr_stop_reason (desc) < 0) {
			dbg->reason.type = R_DEBUG_REASON_UNKNOWN;
			return R_DEBUG_REASON_UNKNOWN;
		}
	}
	if (desc->stop_reason.thread.present) {
		dbg->reason.tid = desc->stop_reason.thread.tid;
		dbg->pid = desc->stop_reason.thread.pid;
		dbg->tid = desc->stop_reason.thread.tid;
		if (dbg->pid != desc->pid || dbg->tid != desc->tid) {
			//eprintf ("= attach %d %d\n", dbg->pid, dbg->tid);
			gdbr_select (desc, dbg->pid, dbg->tid);
		}
	}
	dbg->reason.signum = desc->stop_reason.signum;
	dbg->reason.type = desc->stop_reason.reason;
	return desc->stop_reason.reason;
}