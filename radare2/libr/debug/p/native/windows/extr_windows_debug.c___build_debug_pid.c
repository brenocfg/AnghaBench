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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  RDebugPid ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int PROCESS_QUERY_INFORMATION ; 
 int PROCESS_VM_READ ; 
 scalar_t__ ProcessIdToSessionId (int,int*) ; 
 char* __resolve_path (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * r_debug_pid_new (char*,int,int,char,int /*<<< orphan*/ ) ; 
 char* r_sys_conv_win_to_utf8 (int /*<<< orphan*/  const*) ; 
 scalar_t__ w32_OpenProcess (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static RDebugPid *__build_debug_pid(int pid, HANDLE ph, const TCHAR* name) {
	char *path = NULL;
	int uid = -1;
	if (!ph) {
		ph = w32_OpenProcess (PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
		if (ph) {
			path = __resolve_path (ph, NULL);
			DWORD sid;
			if (ProcessIdToSessionId (pid, &sid)) {
				uid = sid;
			}
			CloseHandle (ph);
		} else {
			return NULL;
		}
	} else {
		path = __resolve_path (ph, NULL);
		DWORD sid;
		if (ProcessIdToSessionId (pid, &sid)) {
			uid = sid;
		}
	}
	if (!path) {
		path = r_sys_conv_win_to_utf8 (name);
	}
	// it is possible to get pc for a non debugged process but the operation is expensive and might be risky
	RDebugPid *ret = r_debug_pid_new (path, pid, uid, 's', 0);
	free (path);
	return ret;
}