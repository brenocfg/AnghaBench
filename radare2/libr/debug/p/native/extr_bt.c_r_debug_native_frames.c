#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct frames_proxy_args {int /*<<< orphan*/  member_2; TYPE_1__* member_1; int /*<<< orphan*/ * (* member_0 ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {scalar_t__ bits; int /*<<< orphan*/  call_frames; scalar_t__ btalgo; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/ * (* RDebugFrameCallback ) (TYPE_1__*,int /*<<< orphan*/ ) ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 scalar_t__ R_SYS_BITS_64 ; 
 int /*<<< orphan*/ * backtrace_fuzzy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backtrace_proxy ; 
 int /*<<< orphan*/ * backtrace_x86_32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * backtrace_x86_32_anal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * backtrace_x86_64 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * backtrace_x86_64_anal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepend_current_pc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_debug_ptrace_func (TYPE_1__*,int /*<<< orphan*/ ,struct frames_proxy_args*) ; 
 int /*<<< orphan*/ * r_list_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static RList *r_debug_native_frames(RDebug *dbg, ut64 at) {
	RDebugFrameCallback cb = NULL;
	if (dbg->btalgo) {
		if (!strcmp (dbg->btalgo, "fuzzy")) {
			cb = backtrace_fuzzy;
		} else if (!strcmp (dbg->btalgo, "anal")) {
			if (dbg->bits == R_SYS_BITS_64) {
				cb = backtrace_x86_64_anal;
			} else {
				cb = backtrace_x86_32_anal;
			}
		}
	}
	if (!cb) {
		if (dbg->bits == R_SYS_BITS_64) {
			cb = backtrace_x86_64;
		} else {
			cb = backtrace_x86_32;
		}
	}

	RList *list;
	if (dbg->btalgo && !strcmp (dbg->btalgo, "trace")) {
		list = r_list_clone (dbg->call_frames);
	} else {
#if HAVE_PTRACE
		struct frames_proxy_args args = { cb, dbg, at };
		list = r_debug_ptrace_func (dbg, backtrace_proxy, &args);
#else
		list = cb (dbg, at);
#endif
	}

	prepend_current_pc (dbg, list);
	return list;
}