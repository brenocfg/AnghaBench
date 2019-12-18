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
 scalar_t__ SIGTRAP ; 
 scalar_t__ WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static void check_success(const char *msg)
{
	const char *msg2;
	int status;

	/* Wait for the child to SIGTRAP */
	wait(&status);

	msg2 = "Failed";

	if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
		msg2 = "Child process hit the breakpoint";
	}

	printf("%s Result: [%s]\n", msg, msg2);
}