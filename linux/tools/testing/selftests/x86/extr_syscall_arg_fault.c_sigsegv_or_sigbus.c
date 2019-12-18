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

/* Variables and functions */
 long EFAULT ; 
 long ENOSYS ; 
 size_t REG_AX ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  n_errs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sigsegv_or_sigbus(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;
	long ax = (long)ctx->uc_mcontext.gregs[REG_AX];

	if (ax != -EFAULT && ax != -ENOSYS) {
		printf("[FAIL]\tAX had the wrong value: 0x%lx\n",
		       (unsigned long)ax);
		n_errs++;
	} else {
		printf("[OK]\tSeems okay\n");
	}

	siglongjmp(jmpbuf, 1);
}