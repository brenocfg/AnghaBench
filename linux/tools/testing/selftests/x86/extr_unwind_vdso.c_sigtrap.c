#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long* gregs; } ;
struct TYPE_4__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct unwind_state {unsigned long ip; int depth; } ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 size_t REG_EFL ; 
 size_t REG_EIP ; 
 size_t REG_ESP ; 
 unsigned long X86_EFLAGS_TF ; 
 int /*<<< orphan*/  _Unwind_Backtrace (int /*<<< orphan*/ ,struct unwind_state*) ; 
 int got_sysinfo ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long return_address ; 
 unsigned long sysinfo ; 
 int /*<<< orphan*/  trace_fn ; 

__attribute__((used)) static void sigtrap(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t *)ctx_void;
	struct unwind_state state;
	unsigned long ip = ctx->uc_mcontext.gregs[REG_EIP];

	if (!got_sysinfo && ip == sysinfo) {
		got_sysinfo = true;

		/* Find the return address. */
		return_address = *(unsigned long *)(unsigned long)ctx->uc_mcontext.gregs[REG_ESP];

		printf("\tIn vsyscall at 0x%lx, returning to 0x%lx\n",
		       ip, return_address);
	}

	if (!got_sysinfo)
		return;		/* Not there yet */

	if (ip == return_address) {
		ctx->uc_mcontext.gregs[REG_EFL] &= ~X86_EFLAGS_TF;
		printf("\tVsyscall is done\n");
		return;
	}

	printf("\tSIGTRAP at 0x%lx\n", ip);

	state.ip = ip;
	state.depth = -1;
	_Unwind_Backtrace(trace_fn, &state);
}