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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u16 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ USHRT_MAX ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ perf_ustack_task_size (struct pt_regs*) ; 
 scalar_t__ round_up (scalar_t__,int) ; 

__attribute__((used)) static u16
perf_sample_ustack_size(u16 stack_size, u16 header_size,
			struct pt_regs *regs)
{
	u64 task_size;

	/* No regs, no stack pointer, no dump. */
	if (!regs)
		return 0;

	/*
	 * Check if we fit in with the requested stack size into the:
	 * - TASK_SIZE
	 *   If we don't, we limit the size to the TASK_SIZE.
	 *
	 * - remaining sample size
	 *   If we don't, we customize the stack size to
	 *   fit in to the remaining sample size.
	 */

	task_size  = min((u64) USHRT_MAX, perf_ustack_task_size(regs));
	stack_size = min(stack_size, (u16) task_size);

	/* Current header size plus static size and dynamic size. */
	header_size += 2 * sizeof(u64);

	/* Do we fit in with the current stack dump size? */
	if ((u16) (header_size + stack_size) < header_size) {
		/*
		 * If we overflow the maximum size for the sample,
		 * we customize the stack dump size to fit in.
		 */
		stack_size = USHRT_MAX - header_size - sizeof(u64);
		stack_size = round_up(stack_size, sizeof(u64));
	}

	return stack_size;
}