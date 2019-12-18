#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_1__* params; } ;
struct TYPE_23__ {TYPE_5__* user; } ;
struct TYPE_22__ {int pid; } ;
struct TYPE_19__ {int dwThreadId; scalar_t__ hProcess; } ;
struct TYPE_21__ {TYPE_3__ pi; TYPE_8__* inst; } ;
struct TYPE_20__ {scalar_t__ length; TYPE_2__* head; } ;
struct TYPE_18__ {scalar_t__ data; } ;
struct TYPE_17__ {int pid; int /*<<< orphan*/  ret; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ RList ;
typedef  TYPE_5__ RIOW32Dbg ;
typedef  TYPE_6__ RDebugPid ;
typedef  TYPE_7__ RDebug ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  W32_ATTACH ; 
 int /*<<< orphan*/  r_list_free (TYPE_4__*) ; 
 TYPE_4__* r_list_new () ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 scalar_t__ w32_OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w32_PROCESS_ALL_ACCESS ; 
 int /*<<< orphan*/  w32_dbg_wait (TYPE_7__*,int) ; 
 TYPE_4__* w32_thread_list (TYPE_7__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  w32dbg_wrap_wait_ret (TYPE_8__*) ; 
 int /*<<< orphan*/  w32dbgw_err (TYPE_8__*) ; 

int w32_attach(RDebug *dbg, int pid) {
	RIOW32Dbg *rio = dbg->user;
	if (rio->pi.hProcess) {
		return rio->pi.dwThreadId;
	}
	HANDLE ph = w32_OpenProcess (w32_PROCESS_ALL_ACCESS, FALSE, pid);
	if (!ph) {
		return -1;
	}
	rio->inst->params->type = W32_ATTACH;
	rio->inst->params->pid = pid;
	w32dbg_wrap_wait_ret (rio->inst);
	if (!rio->inst->params->ret) {
		w32dbgw_err (rio->inst);
		r_sys_perror ("DebugActiveProcess");
		CloseHandle (ph);
		return -1;
	}
	RList *threads = r_list_new ();
	if (!threads) {
		CloseHandle (ph);
		return -1;
	}
	threads = w32_thread_list (dbg, pid, threads);
	if (threads->length == 0) {
		r_list_free (threads);
		CloseHandle (ph);
		return -1;
	}
	int tid = ((RDebugPid *)threads->head->data)->pid;
	r_list_free (threads);
	rio->pi.hProcess = ph;
	w32_dbg_wait (dbg, pid);

	return tid;
}