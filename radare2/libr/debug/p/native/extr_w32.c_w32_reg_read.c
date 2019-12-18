#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_9__ {int /*<<< orphan*/  ContextFlags; } ;
struct TYPE_8__ {int pid; int tid; } ;
typedef  TYPE_1__ RDebug ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_2__ CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_ALL ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ GetThreadContext (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printwincontext (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 int /*<<< orphan*/ * w32_open_thread (int,int) ; 

__attribute__((used)) static int w32_reg_read(RDebug *dbg, int type, ut8 *buf, int size) {
#ifdef _MSC_VER
	CONTEXT ctx;
#else
	CONTEXT ctx __attribute__ ((aligned (16)));
#endif
	int showfpu = false;
	int pid = dbg->pid;
	int tid = dbg->tid;
	HANDLE hThread = NULL;
	if (type < -1) {
		showfpu = true; // hack for debugging
		type = -type;
	}
	hThread = w32_open_thread (pid, tid);
	memset(&ctx, 0, sizeof (CONTEXT));
	ctx.ContextFlags = CONTEXT_ALL ;
	if (GetThreadContext (hThread, &ctx) == TRUE) {
		// on windows we dont need check type alway read/write full arena
		//if (type == R_REG_TYPE_GPR) {
			if (size > sizeof (CONTEXT)) {
				size = sizeof (CONTEXT);
			}
			memcpy (buf, &ctx, size);
		//} else {
		//	size = 0;
		//}
	} else {
		r_sys_perror ("w32_reg_read/GetThreadContext");
		size = 0;
	}
	if (showfpu) {
		printwincontext (hThread, &ctx);
	}
	CloseHandle(hThread);
	return size;
}