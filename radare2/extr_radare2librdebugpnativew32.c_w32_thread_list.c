#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwSize; int th32OwnerProcessID; int /*<<< orphan*/  th32ThreadID; } ;
typedef  TYPE_1__ THREADENTRY32 ;
typedef  int /*<<< orphan*/  RList ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateToolhelp32Snapshot (int /*<<< orphan*/ ,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  TH32CS_SNAPTHREAD ; 
 int /*<<< orphan*/  THREAD_ALL_ACCESS ; 
 int /*<<< orphan*/  Thread32First (scalar_t__,TYPE_1__*) ; 
 scalar_t__ Thread32Next (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_debug_pid_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 scalar_t__ w32_OpenThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RList *w32_thread_list (int pid, RList *list) {
        HANDLE th;
        HANDLE thid;
        THREADENTRY32 te32;

        te32.dwSize = sizeof(THREADENTRY32);

	if (!w32_OpenThread) {
		eprintf("w32_thread_list: no w32_OpenThread?\n");
		return list;
	}
        th = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
        if(th == INVALID_HANDLE_VALUE || !Thread32First (th, &te32))
                goto err_load_th;
        do {
                /* get all threads of process */
                if (te32.th32OwnerProcessID == pid) {
			//te32.dwFlags);
                        /* open a new handler */
			// XXX: fd leak?
#if 0
 75 typedef struct tagTHREADENTRY32 {
 76         DWORD dwSize;
 77         DWORD cntUsage;
 78         DWORD th32ThreadID;
 79         DWORD th32OwnerProcessID;
 80         LONG tpBasePri;
 81         LONG tpDeltaPri;
 82         DWORD dwFlags;
#endif
			thid = w32_OpenThread (THREAD_ALL_ACCESS, 0, te32.th32ThreadID);
			if (!thid) {
				r_sys_perror ("w32_thread_list/OpenThread");
                                goto err_load_th;
			}
			r_list_append (list, r_debug_pid_new ("???", te32.th32ThreadID, 0, 's', 0));
                }
        } while (Thread32Next (th, &te32));
err_load_th:
        if(th != INVALID_HANDLE_VALUE)
                CloseHandle (th);
	return list;
}