#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned long u64 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long TASK_SIZE ; 
 unsigned long perf_user_stack_pointer (struct pt_regs*) ; 

__attribute__((used)) static u64 perf_ustack_task_size(struct pt_regs *regs)
{
	unsigned long addr = perf_user_stack_pointer(regs);

	if (!addr || addr >= TASK_SIZE)
		return 0;

	return TASK_SIZE - addr;
}