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
 int /*<<< orphan*/  cmd_usage () ; 
 int /*<<< orphan*/  exec_cmd_init (char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  handle_internal_command (int,char const**) ; 
 int /*<<< orphan*/  handle_options (int*,char const***) ; 
 scalar_t__ help ; 
 int /*<<< orphan*/  pager_init (char const*) ; 

int main(int argc, const char **argv)
{
	static const char *UNUSED = "OBJTOOL_NOT_IMPLEMENTED";

	/* libsubcmd init */
	exec_cmd_init("objtool", UNUSED, UNUSED, UNUSED);
	pager_init(UNUSED);

	argv++;
	argc--;
	handle_options(&argc, &argv);

	if (!argc || help)
		cmd_usage();

	handle_internal_command(argc, argv);

	return 0;
}