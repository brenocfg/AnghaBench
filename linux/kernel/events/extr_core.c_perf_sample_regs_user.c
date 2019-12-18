#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct perf_regs {struct pt_regs* regs; int /*<<< orphan*/  abi; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_SAMPLE_REGS_ABI_NONE ; 
 int PF_KTHREAD ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  perf_get_regs_user (struct perf_regs*,struct pt_regs*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_reg_abi (TYPE_1__*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static void perf_sample_regs_user(struct perf_regs *regs_user,
				  struct pt_regs *regs,
				  struct pt_regs *regs_user_copy)
{
	if (user_mode(regs)) {
		regs_user->abi = perf_reg_abi(current);
		regs_user->regs = regs;
	} else if (!(current->flags & PF_KTHREAD)) {
		perf_get_regs_user(regs_user, regs, regs_user_copy);
	} else {
		regs_user->abi = PERF_SAMPLE_REGS_ABI_NONE;
		regs_user->regs = NULL;
	}
}