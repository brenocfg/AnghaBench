#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned long pc; int sp; int /*<<< orphan*/  pstate; } ;
struct TYPE_5__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_6__ {TYPE_1__ mm; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PSR_MODE_EL0t ; 
 unsigned long allocate_user_page (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  memcpy (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  set_pgd (int /*<<< orphan*/ ) ; 
 struct pt_regs* task_pt_regs (TYPE_2__*) ; 

int move_to_user_mode(unsigned long start, unsigned long size, unsigned long pc)
{
	struct pt_regs *regs = task_pt_regs(current);
	regs->pstate = PSR_MODE_EL0t;
	regs->pc = pc;
	regs->sp = 2 *  PAGE_SIZE;  
	unsigned long code_page = allocate_user_page(current, 0);
	if (code_page == 0)	{
		return -1;
	}
	memcpy(code_page, start, size);
	set_pgd(current->mm.pgd);
	return 0;
}