#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_8__ {scalar_t__ tid; int /*<<< orphan*/  bits; TYPE_2__* user; } ;
struct TYPE_6__ {scalar_t__ dwThreadId; scalar_t__ hThread; } ;
struct TYPE_7__ {TYPE_1__ pi; } ;
typedef  TYPE_2__ RIOW32Dbg ;
typedef  TYPE_3__ RDebug ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  R_SYS_BITS_64 ; 
 int THREAD_GET_CONTEXT ; 
 int THREAD_QUERY_INFORMATION ; 
 int THREAD_SUSPEND_RESUME ; 
 int __get_thread_context (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int __is_thread_alive (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  __printwincontext (scalar_t__,int /*<<< orphan*/ *) ; 
 int __resume_thread (scalar_t__,int /*<<< orphan*/ ) ; 
 int __suspend_thread (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 scalar_t__ w32_OpenThread (int,int /*<<< orphan*/ ,scalar_t__) ; 

int w32_reg_read(RDebug *dbg, int type, ut8 *buf, int size) {
	bool showfpu = false;
	if (type < -1) {
		showfpu = true; // hack for debugging
		type = -type;
	}
	RIOW32Dbg *rio = dbg->user;

	bool alive = __is_thread_alive (dbg, dbg->tid);
	HANDLE th = rio->pi.dwThreadId == dbg->tid ? rio->pi.hThread : NULL;
	if (!th || th == INVALID_HANDLE_VALUE) {
		DWORD flags = THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT;
		if (dbg->bits == R_SYS_BITS_64) {
				flags |= THREAD_QUERY_INFORMATION;
		}
		th = w32_OpenThread (flags, FALSE, dbg->tid);
		if (!th && alive) {
			r_sys_perror ("w32_reg_read/OpenThread");
		}
		if (!th) {
			return 0;
		}
	}
	// Always suspend
	if (alive && __suspend_thread (th, dbg->bits) == -1) {
		CloseHandle (th);
		return 0;
	}
	size = __get_thread_context (th, buf, size, dbg->bits);
	if (showfpu) {
		__printwincontext (th, (CONTEXT *)buf);
	}
	// Always resume
	if (alive && __resume_thread (th, dbg->bits) == -1) {
		size = 0;
	}
	if (th != rio->pi.hThread) {
		CloseHandle (th);
	}
	return size;
}