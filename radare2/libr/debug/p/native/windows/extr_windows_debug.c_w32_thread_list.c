#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  te ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_14__ {int /*<<< orphan*/  Eip; int /*<<< orphan*/  Rip; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {scalar_t__ bSuspended; scalar_t__ bFinished; } ;
struct TYPE_12__ {int tid; int pid; } ;
struct TYPE_11__ {int dwSize; int th32ThreadID; int th32OwnerProcessID; } ;
typedef  TYPE_1__ THREADENTRY32 ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_2__ RDebug ;
typedef  TYPE_3__* PTHREAD_ITEM ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_4__ CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int PROCESS_QUERY_INFORMATION ; 
 int PROCESS_VM_READ ; 
 scalar_t__ ProcessIdToSessionId (int,int*) ; 
 char R_DBG_PROC_DEAD ; 
 char R_DBG_PROC_RUN ; 
 char R_DBG_PROC_SLEEP ; 
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 int /*<<< orphan*/  TH32CS_SNAPTHREAD ; 
 scalar_t__ Thread32First (scalar_t__,TYPE_1__*) ; 
 scalar_t__ Thread32Next (scalar_t__,TYPE_1__*) ; 
 TYPE_3__* __find_thread (TYPE_2__*,int) ; 
 char* __resolve_path (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_debug_pid_new (char*,int,int,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 char* strdup (char*) ; 
 scalar_t__ w32_CreateToolhelp32Snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ w32_OpenProcess (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w32_reg_read (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

RList *w32_thread_list(RDebug *dbg, int pid, RList *list) {
	// pid is not respected for TH32CS_SNAPTHREAD flag
	HANDLE th = w32_CreateToolhelp32Snapshot (TH32CS_SNAPTHREAD, 0);
	if (th == INVALID_HANDLE_VALUE) {
		r_sys_perror ("w32_thread_list/CreateToolhelp32Snapshot");
		return list;
	}
	THREADENTRY32 te;
	te.dwSize = sizeof (te);
	HANDLE ph = w32_OpenProcess (PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (Thread32First (th, &te)) {
		// TODO: export this code to its own function?
		char *path = NULL;
		int uid = -1;
		if (!te.th32ThreadID) {
			path = __resolve_path (ph, NULL);
			DWORD sid;
			if (ProcessIdToSessionId (pid, &sid)) {
				uid = sid;
			}
		}
		if (!path) {
			// TODO: enum processes to get binary's name
			path = strdup ("???");
		}
		int saved_tid = dbg->tid;
		do {
			char status = R_DBG_PROC_SLEEP;
			if (te.th32OwnerProcessID == pid) {
				ut64 pc = 0;
				if (dbg->pid == pid) {
					CONTEXT ctx = {0};
					dbg->tid = te.th32ThreadID;
					w32_reg_read (dbg, R_REG_TYPE_GPR, (ut8 *)&ctx, sizeof (ctx));
					// TODO: is needed check context for x32 and x64??
#if _WIN64
					pc = ctx.Rip;
#else
					pc = ctx.Eip;
#endif
					PTHREAD_ITEM pthread = __find_thread (dbg, te.th32ThreadID);
					if (pthread) {
						if (pthread->bFinished) {
							status = R_DBG_PROC_DEAD;
						} else if (pthread->bSuspended) {
							status = R_DBG_PROC_SLEEP;
						} else {
							status = R_DBG_PROC_RUN; // TODO: Get more precise thread status
						}
					}
				}
				r_list_append (list, r_debug_pid_new (path, te.th32ThreadID, uid, status, pc));
			}
		} while (Thread32Next (th, &te));
		dbg->tid = saved_tid;
		free (path);
	} else {
		r_sys_perror ("w32_thread_list/Thread32First");
	}
	CloseHandle (th);
	return list;
}