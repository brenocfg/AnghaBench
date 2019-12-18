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
struct TYPE_4__ {scalar_t__* fp_regs; } ;
struct TYPE_3__ {TYPE_2__ uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int bad_context ; 
 scalar_t__* darray ; 

void signal_fpu_sig(int sig, siginfo_t *info, void *context)
{
	int i;
	ucontext_t *uc = context;
	mcontext_t *mc = &uc->uc_mcontext;

	/* Only the non volatiles were loaded up */
	for (i = 14; i < 32; i++) {
		if (mc->fp_regs[i] != darray[i - 14]) {
			bad_context = true;
			break;
		}
	}
}