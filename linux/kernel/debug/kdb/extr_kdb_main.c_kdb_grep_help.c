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
 int /*<<< orphan*/  kdb_printf (char*) ; 

__attribute__((used)) static int kdb_grep_help(int argc, const char **argv)
{
	kdb_printf("Usage of  cmd args | grep pattern:\n");
	kdb_printf("  Any command's output may be filtered through an ");
	kdb_printf("emulated 'pipe'.\n");
	kdb_printf("  'grep' is just a key word.\n");
	kdb_printf("  The pattern may include a very limited set of "
		   "metacharacters:\n");
	kdb_printf("   pattern or ^pattern or pattern$ or ^pattern$\n");
	kdb_printf("  And if there are spaces in the pattern, you may "
		   "quote it:\n");
	kdb_printf("   \"pat tern\" or \"^pat tern\" or \"pat tern$\""
		   " or \"^pat tern$\"\n");
	return 0;
}