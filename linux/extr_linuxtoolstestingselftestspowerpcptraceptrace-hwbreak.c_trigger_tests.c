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
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_var (int) ; 
 int /*<<< orphan*/  write_var (int) ; 

__attribute__((used)) static void trigger_tests(void)
{
	int len, ret;

	ret = ptrace(PTRACE_TRACEME, 0, NULL, 0);
	if (ret) {
		perror("Can't be traced?\n");
		return;
	}

	/* Wake up father so that it sets up the first test */
	kill(getpid(), SIGUSR1);

	/* Test write watchpoints */
	for (len = 1; len <= sizeof(long); len <<= 1)
		write_var(len);

	/* Test read/write watchpoints (on read accesses) */
	for (len = 1; len <= sizeof(long); len <<= 1)
		read_var(len);

	/* Test when breakpoint is unset */

	/* Test write watchpoints */
	for (len = 1; len <= sizeof(long); len <<= 1)
		write_var(len);

	/* Test read/write watchpoints (on read accesses) */
	for (len = 1; len <= sizeof(long); len <<= 1)
		read_var(len);
}