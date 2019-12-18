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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__ RDebug ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int R_REG_TYPE_DRX ; 
 int /*<<< orphan*/  R_SYS_BITS_64 ; 
 int THREAD_QUERY_INFORMATION ; 
 int THREAD_SET_CONTEXT ; 
 int THREAD_SUSPEND_RESUME ; 
 int __is_thread_alive (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int __resume_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __set_thread_context (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int __suspend_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __transfer_drx (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 int /*<<< orphan*/  w32_OpenThread (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int w32_reg_write(RDebug *dbg, int type, const ut8 *buf, int size) {
	DWORD flags = THREAD_SUSPEND_RESUME | THREAD_SET_CONTEXT;
	if (dbg->bits == R_SYS_BITS_64) {
		flags |= THREAD_QUERY_INFORMATION;
	}
	HANDLE th = w32_OpenThread (flags, FALSE, dbg->tid);
	if (!th) {
		r_sys_perror ("w32_reg_write/OpenThread");
		return false;
	}
	bool alive = __is_thread_alive (dbg, dbg->tid);
	// Always suspend
	if (alive && __suspend_thread (th, dbg->bits) == -1) {
		CloseHandle (th);
		return false;
	}
	if (type == R_REG_TYPE_DRX) {
		__transfer_drx (dbg, buf);
	}
	bool ret = __set_thread_context (th, buf, size, dbg->bits);
	// Always resume
	if (alive && __resume_thread (th, dbg->bits) == -1) {
		ret = false;
	}
	CloseHandle (th);
	return ret;
}