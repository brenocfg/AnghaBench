#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dwSize; int th32ProcessID; int th32ParentProcessID; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RDebugPid ;
typedef  TYPE_1__ PROCESSENTRY32 ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateToolhelp32Snapshot (int /*<<< orphan*/ ,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  Process32First (scalar_t__,TYPE_1__*) ; 
 scalar_t__ Process32Next (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  TH32CS_SNAPPROCESS ; 
 int /*<<< orphan*/ * build_debug_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 

RList *w32_pids(int pid, RList *list) {
	HANDLE process_snapshot;
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof (PROCESSENTRY32);
	bool show_all_pids = pid == 0;

	process_snapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, pid);
	if (process_snapshot == INVALID_HANDLE_VALUE) {
		r_sys_perror ("w32_pids/CreateToolhelp32Snapshot");
		return list;
	}
	if (!Process32First (process_snapshot, &pe)) {
		r_sys_perror ("w32_pids/Process32First");
		CloseHandle (process_snapshot);
		return list;
	}
	do {
		if (show_all_pids ||
			pe.th32ProcessID == pid ||
			pe.th32ParentProcessID == pid) {

			RDebugPid *debug_pid = build_debug_pid (&pe);
			if (debug_pid) {
				r_list_append (list, debug_pid);
			}
		}
	} while (Process32Next (process_snapshot, &pe));

	CloseHandle (process_snapshot);
	return list;
}