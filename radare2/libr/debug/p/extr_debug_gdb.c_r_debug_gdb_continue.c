#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tid; scalar_t__ present; } ;
struct TYPE_6__ {TYPE_1__ thread; scalar_t__ is_valid; } ;
struct TYPE_7__ {int tid; TYPE_2__ stop_reason; } ;
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 int R_DEBUG_REASON_UNKNOWN ; 
 int /*<<< orphan*/  check_connection (int /*<<< orphan*/ *) ; 
 TYPE_3__* desc ; 
 int /*<<< orphan*/  gdbr_continue (TYPE_3__*,int,int,int) ; 

__attribute__((used)) static int r_debug_gdb_continue(RDebug *dbg, int pid, int tid, int sig) {
	check_connection (dbg);
	if (!desc) {
		return R_DEBUG_REASON_UNKNOWN;
	}
	gdbr_continue (desc, pid, -1, sig); // Continue all threads
	if (desc->stop_reason.is_valid && desc->stop_reason.thread.present) {
		//if (desc->tid != desc->stop_reason.thread.tid) {
		//	eprintf ("thread id (%d) in reason differs from current thread id (%d)\n", dbg->pid, dbg->tid);
		//}
		desc->tid = desc->stop_reason.thread.tid;
	}
	return desc->tid;
}