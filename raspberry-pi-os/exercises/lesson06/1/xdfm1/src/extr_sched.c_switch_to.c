#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pgd; } ;
struct task_struct {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_switch_to (struct task_struct*,struct task_struct*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  set_pgd (int /*<<< orphan*/ ) ; 

void switch_to(struct task_struct * next) 
{
	if (current == next) 
		return;
	struct task_struct * prev = current;
	current = next;
	set_pgd(next->mm.pgd);
	cpu_switch_to(prev, next);
}