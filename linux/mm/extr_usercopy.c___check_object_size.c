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
#define  GOOD_FRAME 130 
#define  GOOD_STACK 129 
#define  NOT_STACK 128 
 int /*<<< orphan*/  bypass_usercopy_checks ; 
 int /*<<< orphan*/  check_bogus_address (unsigned long const,unsigned long,int) ; 
 int /*<<< orphan*/  check_heap_object (void const*,unsigned long,int) ; 
 int /*<<< orphan*/  check_kernel_text_object (unsigned long const,unsigned long,int) ; 
 int check_stack_object (void const*,unsigned long) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usercopy_abort (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned long) ; 

void __check_object_size(const void *ptr, unsigned long n, bool to_user)
{
	if (static_branch_unlikely(&bypass_usercopy_checks))
		return;

	/* Skip all tests if size is zero. */
	if (!n)
		return;

	/* Check for invalid addresses. */
	check_bogus_address((const unsigned long)ptr, n, to_user);

	/* Check for bad stack object. */
	switch (check_stack_object(ptr, n)) {
	case NOT_STACK:
		/* Object is not touching the current process stack. */
		break;
	case GOOD_FRAME:
	case GOOD_STACK:
		/*
		 * Object is either in the correct frame (when it
		 * is possible to check) or just generally on the
		 * process stack (when frame checking not available).
		 */
		return;
	default:
		usercopy_abort("process stack", NULL, to_user, 0, n);
	}

	/* Check for bad heap object. */
	check_heap_object(ptr, n, to_user);

	/* Check for object in kernel to avoid text exposure. */
	check_kernel_text_object((const unsigned long)ptr, n, to_user);
}