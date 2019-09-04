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
struct TYPE_3__ {scalar_t__* gregs; } ;
struct TYPE_4__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  gregset_t ;

/* Variables and functions */
 size_t REG_EFL ; 
 size_t REG_R11 ; 
 size_t REG_RCX ; 
 size_t REG_RIP ; 
 int /*<<< orphan*/  SA_RESETHAND ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  initial_regs ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__**,int) ; 
 void* rip ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsegv_for_sigreturn_test ; 

__attribute__((used)) static void sigusr1(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	memcpy(&initial_regs, &ctx->uc_mcontext.gregs, sizeof(gregset_t));

	/* Set IP and CX to match so that SYSRET can happen. */
	ctx->uc_mcontext.gregs[REG_RIP] = rip;
	ctx->uc_mcontext.gregs[REG_RCX] = rip;

	/* R11 and EFLAGS should already match. */
	assert(ctx->uc_mcontext.gregs[REG_EFL] ==
	       ctx->uc_mcontext.gregs[REG_R11]);

	sethandler(SIGSEGV, sigsegv_for_sigreturn_test, SA_RESETHAND);

	return;
}