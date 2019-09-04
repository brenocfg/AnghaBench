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
 int /*<<< orphan*/  cmdline (int,char**) ; 
 scalar_t__ dump_only ; 
 int /*<<< orphan*/  flush_output_stdout () ; 
 int fork_it (char**) ; 
 int get_and_dump_counters () ; 
 scalar_t__ list_header_only ; 
 int optind ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  print_header (char*) ; 
 int /*<<< orphan*/  print_version () ; 
 int /*<<< orphan*/  probe_sysfs () ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  turbostat_init () ; 
 int /*<<< orphan*/  turbostat_loop () ; 

int main(int argc, char **argv)
{
	outf = stderr;
	cmdline(argc, argv);

	if (!quiet)
		print_version();

	probe_sysfs();

	turbostat_init();

	/* dump counters and exit */
	if (dump_only)
		return get_and_dump_counters();

	/* list header and exit */
	if (list_header_only) {
		print_header(",");
		flush_output_stdout();
		return 0;
	}

	/*
	 * if any params left, it must be a command to fork
	 */
	if (argc - optind)
		return fork_it(argv + optind);
	else
		turbostat_loop();

	return 0;
}