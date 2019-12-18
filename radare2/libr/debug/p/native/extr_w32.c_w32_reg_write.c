#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_8__ {int /*<<< orphan*/  ContextFlags; } ;
struct TYPE_7__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ RDebug ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_2__ CONTEXT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_ALL ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetThreadContext (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ SetThreadContext (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  w32_open_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w32_reg_write(RDebug *dbg, int type, const ut8* buf, int size) {
	BOOL ret = false;
	HANDLE thread;
#if _MSC_VER
	CONTEXT ctx;
#else
	CONTEXT ctx __attribute__((aligned (16)));
#endif
	thread = w32_open_thread (dbg->pid, dbg->tid);
	ctx.ContextFlags = CONTEXT_ALL;
	GetThreadContext (thread, &ctx);
	// on windows we dont need check type alway read/write full arena
	//if (type == R_REG_TYPE_GPR) {
		if (size > sizeof (CONTEXT)) {
			size = sizeof (CONTEXT);
		}
		memcpy (&ctx, buf, size);
		ret = SetThreadContext (thread, &ctx)? true: false;
	//}
	CloseHandle (thread);
	return ret;
}