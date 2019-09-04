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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  current ; 
 int object_is_on_stack (void*) ; 
 int /*<<< orphan*/  pr_warn (char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_stack_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void debug_object_is_on_stack(void *addr, int onstack)
{
	int is_on_stack;
	static int limit;

	if (limit > 4)
		return;

	is_on_stack = object_is_on_stack(addr);
	if (is_on_stack == onstack)
		return;

	limit++;
	if (is_on_stack)
		pr_warn("object %p is on stack %p, but NOT annotated.\n", addr,
			 task_stack_page(current));
	else
		pr_warn("object %p is NOT on stack %p, but annotated.\n", addr,
			 task_stack_page(current));

	WARN_ON(1);
}