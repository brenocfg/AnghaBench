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
struct TYPE_5__ {struct pt_regs* regs; } ;
struct TYPE_6__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct pt_regs {int nip; } ;
struct TYPE_7__ {int /*<<< orphan*/  si_code; } ;
typedef  TYPE_3__ siginfo_t ;

/* Variables and functions */
 int faulted ; 
 int /*<<< orphan*/  si_code ; 

__attribute__((used)) static void segv_handler(int n, siginfo_t *info, void *ctxt_v)
{
	ucontext_t *ctxt = (ucontext_t *)ctxt_v;
	struct pt_regs *regs = ctxt->uc_mcontext.regs;

	faulted = true;
	si_code = info->si_code;
	regs->nip += 4;
}