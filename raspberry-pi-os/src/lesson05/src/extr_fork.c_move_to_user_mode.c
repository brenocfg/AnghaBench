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
struct pt_regs {unsigned long pc; scalar_t__ sp; int /*<<< orphan*/  pstate; } ;
struct TYPE_3__ {unsigned long stack; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PSR_MODE_EL0t ; 
 TYPE_1__* current ; 
 unsigned long get_free_page () ; 
 int /*<<< orphan*/  memzero (unsigned long,int) ; 
 struct pt_regs* task_pt_regs (TYPE_1__*) ; 

int move_to_user_mode(unsigned long pc)
{
	struct pt_regs *regs = task_pt_regs(current);
	memzero((unsigned long)regs, sizeof(*regs));
	regs->pc = pc;
	regs->pstate = PSR_MODE_EL0t;
	unsigned long stack = get_free_page(); //allocate new user stack
	if (!stack) {
		return -1;
	}
	regs->sp = stack + PAGE_SIZE;
	current->stack = stack;
	return 0;
}