#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  core; scalar_t__ (* cfggeti ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_10__ {TYPE_1__ corebind; TYPE_3__* user; } ;
struct TYPE_8__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  dwProcessId; } ;
struct TYPE_9__ {TYPE_2__ pi; } ;
typedef  TYPE_3__ RIOW32Dbg ;
typedef  TYPE_4__ RDebug ;

/* Variables and functions */
 int breaked ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  w32_DebugBreakProcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w32_select (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void w32_break_process(RDebug *dbg) {
	RIOW32Dbg *rio = dbg->user;
	if (dbg->corebind.cfggeti (dbg->corebind.core, "dbg.threads")) {
		w32_select (dbg, rio->pi.dwProcessId, 0); // Suspend all threads
	} else {
		if (!w32_DebugBreakProcess (rio->pi.hProcess)) {
			r_sys_perror ("w32_break_process/DebugBreakProcess");
			eprintf("Could not interrupt program, attempt to press Ctrl-C in the program's console.\n");
		}
	}

	breaked = true;
}