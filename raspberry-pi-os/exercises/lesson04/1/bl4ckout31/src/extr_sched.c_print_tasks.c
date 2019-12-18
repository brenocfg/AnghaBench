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
struct TYPE_2__ {int sp; } ;
struct task_struct {TYPE_1__ cpu_context; } ;

/* Variables and functions */
 int NR_TASKS ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 struct task_struct** task ; 

void print_tasks() 
{
	struct task_struct *t = task[0];
	for (int i = 0; (i < NR_TASKS) && t; i++){
		t = task[i];
		if (t) {
			printf("    %d: sp: 0x%x\r\n", i, t->cpu_context.sp);
		}
	}
}