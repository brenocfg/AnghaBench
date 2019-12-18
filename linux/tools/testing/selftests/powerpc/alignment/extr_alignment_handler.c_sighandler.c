#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* gp_regs; TYPE_1__* uc_regs; } ;
struct TYPE_6__ {TYPE_2__ uc_mcontext; } ;
typedef  TYPE_3__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_4__ {int* gregs; } ;

/* Variables and functions */
 size_t PT_NIP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int gotsig ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testing ; 

void sighandler(int sig, siginfo_t *info, void *ctx)
{
	ucontext_t *ucp = ctx;

	if (!testing) {
		signal(sig, SIG_DFL);
		kill(0, sig);
	}
	gotsig = sig;
#ifdef __powerpc64__
	ucp->uc_mcontext.gp_regs[PT_NIP] += 4;
#else
	ucp->uc_mcontext.uc_regs->gregs[PT_NIP] += 4;
#endif
}