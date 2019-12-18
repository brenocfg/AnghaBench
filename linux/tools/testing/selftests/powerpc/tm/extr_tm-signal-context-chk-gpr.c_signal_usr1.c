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
struct TYPE_3__ {scalar_t__* gp_regs; } ;
struct TYPE_4__ {TYPE_1__ uc_mcontext; struct TYPE_4__* uc_link; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int NV_GPR_REGS ; 
 int R14 ; 
 int broken ; 
 int fail ; 
 scalar_t__* gprs ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void signal_usr1(int signum, siginfo_t *info, void *uc)
{
	int i;
	ucontext_t *ucp = uc;
	ucontext_t *tm_ucp = ucp->uc_link;

	/* Check first context. Print all mismatches. */
	for (i = 0; i < NV_GPR_REGS; i++) {
		fail = (ucp->uc_mcontext.gp_regs[R14 + i] != gprs[i]);
		if (fail) {
			broken = 1;
			printf("GPR%d (1st context) == %lu instead of %lu (expected)\n",
				R14 + i, ucp->uc_mcontext.gp_regs[R14 + i], gprs[i]);
		}
	}

	/* Check second context. Print all mismatches. */
	for (i = 0; i < NV_GPR_REGS; i++) {
		fail = (tm_ucp->uc_mcontext.gp_regs[R14 + i] != gprs[NV_GPR_REGS + i]);
		if (fail) {
			broken = 1;
			printf("GPR%d (2nd context) == %lu instead of %lu (expected)\n",
				R14 + i, tm_ucp->uc_mcontext.gp_regs[R14 + i], gprs[NV_GPR_REGS + i]);
		}
	}
}