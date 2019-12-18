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
struct TYPE_5__ {TYPE_1__* uc_regs; scalar_t__* gp_regs; } ;
struct TYPE_6__ {TYPE_2__ uc_mcontext; } ;
typedef  TYPE_3__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_4__ {scalar_t__* gregs; } ;

/* Variables and functions */
 size_t PT_NIP ; 
 int /*<<< orphan*/  _exit (int) ; 
 unsigned int expected_instruction ; 
 unsigned int instruction_mask ; 

void signal_action_handler(int signal_num, siginfo_t *info, void *ptr)
{
	ucontext_t *ctx = ptr;
#ifdef __powerpc64__
	unsigned int *pc = (unsigned int *)ctx->uc_mcontext.gp_regs[PT_NIP];
#else
	unsigned int *pc = (unsigned int *)ctx->uc_mcontext.uc_regs->gregs[PT_NIP];
#endif

	/*
	 * Check that the signal was on the correct instruction, using a
	 * mask because the compiler assigns the register at RB.
	 */
	if ((*pc & instruction_mask) == expected_instruction)
		_exit(0); /* We hit the right instruction */

	_exit(1);
}