#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ RDebug ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PROCESS_ALL_ACCESS ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 int /*<<< orphan*/  w32_DebugBreakProcess (scalar_t__) ; 
 scalar_t__ w32_OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void w32_break_process(void *d) {
	RDebug *dbg = (RDebug *)d;
	HANDLE h_proc = w32_OpenProcess (PROCESS_ALL_ACCESS, FALSE, dbg->pid);
	if (!h_proc) {
		r_sys_perror ("w32_break_process/w32_OpenProcess");
		goto err_w32_break_process;
	}
	if (!w32_DebugBreakProcess (h_proc)) {
		r_sys_perror ("w32_break_process/w32_DebugBreakProcess");
		goto err_w32_break_process;
	}
err_w32_break_process:
	if (h_proc) {
		CloseHandle (h_proc);
	}
}