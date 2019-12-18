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
typedef  int /*<<< orphan*/  RDebug ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int PROCESS_TERMINATE ; 
 int SYNCHRONIZE ; 
 scalar_t__ TerminateProcess (scalar_t__,int) ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 int /*<<< orphan*/  w32_DebugActiveProcessStop (int) ; 
 scalar_t__ w32_OpenProcess (int,int /*<<< orphan*/ ,int) ; 

bool w32_terminate_process(RDebug *dbg, int pid) {
	HANDLE h_proc = w32_OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE , FALSE, pid);
	bool ret = false;
	if (!h_proc) {
		r_sys_perror ("w32_terminate_process/OpenProcess");
		goto err_w32_terminate_process;
	}
	/* stop debugging if we are still attached */
	if (w32_DebugActiveProcessStop) {
		w32_DebugActiveProcessStop (pid); //DebugActiveProcessStop (pid);
	}
	if (TerminateProcess (h_proc, 1) == 0) {
		r_sys_perror ("e32_terminate_process/TerminateProcess");
		goto err_w32_terminate_process;

	}
	/* wait up to one second to give the process some time to exit */
	DWORD ret_wait = WaitForSingleObject (h_proc, 1000);
	if (ret_wait == WAIT_FAILED) {
		r_sys_perror ("w32_terminate_process/WaitForSingleObject");
		goto err_w32_terminate_process;
	}
	if (ret_wait == WAIT_TIMEOUT) {
		eprintf ("(%d) Waiting for process to terminate timed out.\n", pid);
		goto err_w32_terminate_process;
	}
	ret = true;
err_w32_terminate_process:
	if (h_proc) {
		CloseHandle (h_proc);
	}
	return ret;
}