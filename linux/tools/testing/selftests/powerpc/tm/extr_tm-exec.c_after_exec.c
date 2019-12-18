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
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure_is_nesting () ; 

__attribute__((used)) static int after_exec(void)
{
	asm __volatile__(
		"tbegin.;"
		"blt    1f;"
		"tsuspend.;"
		"1: ;"
		: : : "memory");

	FAIL_IF(failure_is_nesting());
	return 0;
}