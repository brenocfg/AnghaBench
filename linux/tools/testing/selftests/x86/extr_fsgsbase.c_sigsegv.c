#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* gregs; } ;
struct TYPE_6__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct TYPE_7__ {scalar_t__ si_addr; } ;
typedef  TYPE_3__ siginfo_t ;

/* Variables and functions */
 size_t REG_RIP ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  clearhandler (int /*<<< orphan*/ ) ; 
 unsigned long segv_addr ; 
 int want_segv ; 

__attribute__((used)) static void sigsegv(int sig, siginfo_t *si, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (!want_segv) {
		clearhandler(SIGSEGV);
		return;  /* Crash cleanly. */
	}

	want_segv = false;
	segv_addr = (unsigned long)si->si_addr;

	ctx->uc_mcontext.gregs[REG_RIP] += 4;	/* Skip the faulting mov */

}