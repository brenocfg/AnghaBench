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
 size_t backtrace (void**,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static void test_dump_stack(void)
{
	/*
	 * Build and run this command:
	 *
	 *	addr2line -s -e /proc/$PPID/exe -fpai {backtrace addresses} | \
	 *		grep -v test_dump_stack | cat -n 1>&2
	 *
	 * Note that the spacing is different and there's no newline.
	 */
	size_t i;
	size_t n = 20;
	void *stack[n];
	const char *addr2line = "addr2line -s -e /proc/$PPID/exe -fpai";
	const char *pipeline = "|cat -n 1>&2";
	char cmd[strlen(addr2line) + strlen(pipeline) +
		 /* N bytes per addr * 2 digits per byte + 1 space per addr: */
		 n * (((sizeof(void *)) * 2) + 1) +
		 /* Null terminator: */
		 1];
	char *c;

	n = backtrace(stack, n);
	c = &cmd[0];
	c += sprintf(c, "%s", addr2line);
	/*
	 * Skip the first 3 frames: backtrace, test_dump_stack, and
	 * test_assert. We hope that backtrace isn't inlined and the other two
	 * we've declared noinline.
	 */
	for (i = 2; i < n; i++)
		c += sprintf(c, " %lx", ((unsigned long) stack[i]) - 1);
	c += sprintf(c, "%s", pipeline);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
	system(cmd);
#pragma GCC diagnostic pop
}