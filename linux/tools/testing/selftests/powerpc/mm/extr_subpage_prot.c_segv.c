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
struct TYPE_3__ {struct pt_regs* regs; } ;
struct TYPE_4__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct pt_regs {int nip; scalar_t__ dar; } ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 void* dar ; 
 int /*<<< orphan*/  exit (int) ; 
 int faulted ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  in_test ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void segv(int signum, siginfo_t *info, void *ctxt_v)
{
	ucontext_t *ctxt = (ucontext_t *)ctxt_v;
	struct pt_regs *regs = ctxt->uc_mcontext.regs;

	if (!in_test) {
		fprintf(stderr, "Segfault outside of test !\n");
		exit(1);
	}

	faulted = 1;
	dar = (void *)regs->dar;
	regs->nip += 4;
}