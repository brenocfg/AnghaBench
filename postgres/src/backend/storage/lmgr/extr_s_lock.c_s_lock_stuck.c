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
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*,char const*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
s_lock_stuck(const char *file, int line, const char *func)
{
	if (!func)
		func = "(unknown)";
#if defined(S_LOCK_TEST)
	fprintf(stderr,
			"\nStuck spinlock detected at %s, %s:%d.\n",
			func, file, line);
	exit(1);
#else
	elog(PANIC, "stuck spinlock detected at %s, %s:%d",
		 func, file, line);
#endif
}