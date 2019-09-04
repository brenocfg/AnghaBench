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
struct unwind_libunwind_ops {int dummy; } ;
struct thread {struct unwind_libunwind_ops* unwind_libunwind_ops; } ;

/* Variables and functions */

__attribute__((used)) static void unwind__register_ops(struct thread *thread,
			  struct unwind_libunwind_ops *ops)
{
	thread->unwind_libunwind_ops = ops;
}