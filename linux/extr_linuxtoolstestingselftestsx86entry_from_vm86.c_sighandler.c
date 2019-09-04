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
struct TYPE_3__ {int* gregs; } ;
struct TYPE_4__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 size_t REG_CS ; 
 size_t REG_EFL ; 
 int SIGILL ; 
 int SIGSEGV ; 
 int X86_EFLAGS_VM ; 
 int got_signal ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void sighandler(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (ctx->uc_mcontext.gregs[REG_EFL] & X86_EFLAGS_VM ||
	    (ctx->uc_mcontext.gregs[REG_CS] & 3) != 3) {
		printf("[FAIL]\tSignal frame should not reflect vm86 mode\n");
		nerrs++;
	}

	const char *signame;
	if (sig == SIGSEGV)
		signame = "SIGSEGV";
	else if (sig == SIGILL)
		signame = "SIGILL";
	else
		signame = "unexpected signal";

	printf("[INFO]\t%s: FLAGS = 0x%lx, CS = 0x%hx\n", signame,
	       (unsigned long)ctx->uc_mcontext.gregs[REG_EFL],
	       (unsigned short)ctx->uc_mcontext.gregs[REG_CS]);

	got_signal = 1;
}