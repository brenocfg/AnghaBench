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
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int test_exec(void)
{
	SKIP_IF(!have_htm());

	asm __volatile__(
		"tbegin.;"
		"blt    1f; "
		"tsuspend.;"
		"1: ;"
		: : : "memory");

	execl(path, "tm-exec", "--child", NULL);

	/* Shouldn't get here */
	perror("execl() failed");
	return 1;
}