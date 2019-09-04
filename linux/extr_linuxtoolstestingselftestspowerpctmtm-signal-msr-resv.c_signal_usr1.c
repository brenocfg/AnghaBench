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
struct TYPE_5__ {TYPE_1__* uc_regs; } ;
struct TYPE_6__ {TYPE_2__ uc_mcontext; struct TYPE_6__* uc_link; } ;
typedef  TYPE_3__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_4__ {unsigned long long* gregs; } ;

/* Variables and functions */
 size_t PT_MSR ; 
 int segv_expected ; 

void signal_usr1(int signum, siginfo_t *info, void *uc)
{
	ucontext_t *ucp = uc;

	/* Link tm checkpointed context to normal context */
	ucp->uc_link = ucp;
	/* Set all TM bits so that the context is now invalid */
#ifdef __powerpc64__
	ucp->uc_mcontext.gp_regs[PT_MSR] |= (7ULL << 32);
#else
	ucp->uc_mcontext.uc_regs->gregs[PT_MSR] |= (7ULL);
#endif
	/* Should segv on return becuase of invalid context */
	segv_expected = 1;
}