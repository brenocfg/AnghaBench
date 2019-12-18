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
struct TYPE_6__ {TYPE_1__* v_regs; } ;
struct TYPE_5__ {TYPE_3__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  TYPE_3__ mcontext_t ;
struct TYPE_4__ {int** vrregs; } ;

/* Variables and functions */
 int bad_context ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ ** varray ; 

void signal_vmx_sig(int sig, siginfo_t *info, void *context)
{
	int i;
	ucontext_t *uc = context;
	mcontext_t *mc = &uc->uc_mcontext;

	/* Only the non volatiles were loaded up */
	for (i = 20; i < 32; i++) {
		if (memcmp(mc->v_regs->vrregs[i], &varray[i - 20], 16)) {
			int j;
			/*
			 * Shouldn't printf() in a signal handler, however, this is a
			 * test and we've detected failure. Understanding what failed
			 * is paramount. All that happens after this is tests exit with
			 * failure.
			 */
			printf("VMX mismatch at reg %d!\n", i);
			printf("Reg | Actual                  | Expected\n");
			for (j = 20; j < 32; j++) {
				printf("%d  | 0x%04x%04x%04x%04x      | 0x%04x%04x%04x%04x\n", j, mc->v_regs->vrregs[j][0],
					   mc->v_regs->vrregs[j][1], mc->v_regs->vrregs[j][2], mc->v_regs->vrregs[j][3],
					   varray[j - 20][0], varray[j - 20][1], varray[j - 20][2], varray[j - 20][3]);
			}
			bad_context = true;
			break;
		}
	}
}