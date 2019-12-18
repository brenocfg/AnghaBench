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
 int ia64_get_bsp () ; 
 long max_stack_depth_bytes ; 
 int /*<<< orphan*/ * register_stack_base_ptr ; 
 char* stack_base_ptr ; 

bool
stack_is_too_deep(void)
{
	char		stack_top_loc;
	long		stack_depth;

	/*
	 * Compute distance from reference point to my local variables
	 */
	stack_depth = (long) (stack_base_ptr - &stack_top_loc);

	/*
	 * Take abs value, since stacks grow up on some machines, down on others
	 */
	if (stack_depth < 0)
		stack_depth = -stack_depth;

	/*
	 * Trouble?
	 *
	 * The test on stack_base_ptr prevents us from erroring out if called
	 * during process setup or in a non-backend process.  Logically it should
	 * be done first, but putting it here avoids wasting cycles during normal
	 * cases.
	 */
	if (stack_depth > max_stack_depth_bytes &&
		stack_base_ptr != NULL)
		return true;

	/*
	 * On IA64 there is a separate "register" stack that requires its own
	 * independent check.  For this, we have to measure the change in the
	 * "BSP" pointer from PostgresMain to here.  Logic is just as above,
	 * except that we know IA64's register stack grows up.
	 *
	 * Note we assume that the same max_stack_depth applies to both stacks.
	 */
#if defined(__ia64__) || defined(__ia64)
	stack_depth = (long) (ia64_get_bsp() - register_stack_base_ptr);

	if (stack_depth > max_stack_depth_bytes &&
		register_stack_base_ptr != NULL)
		return true;
#endif							/* IA64 */

	return false;
}