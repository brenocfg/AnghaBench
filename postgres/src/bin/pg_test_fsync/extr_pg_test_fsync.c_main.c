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
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  get_progname (char*) ; 
 int /*<<< orphan*/  handle_args (int,char**) ; 
 int /*<<< orphan*/  pg_logging_init (char*) ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_buf () ; 
 int /*<<< orphan*/  process_alarm ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_cleanup ; 
 int /*<<< orphan*/  test_file_descriptor_sync () ; 
 int /*<<< orphan*/  test_non_sync () ; 
 int /*<<< orphan*/  test_open () ; 
 int /*<<< orphan*/  test_open_syncs () ; 
 int /*<<< orphan*/  test_sync (int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	pg_logging_init(argv[0]);
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pg_test_fsync"));
	progname = get_progname(argv[0]);

	handle_args(argc, argv);

	/* Prevent leaving behind the test file */
	pqsignal(SIGINT, signal_cleanup);
	pqsignal(SIGTERM, signal_cleanup);
#ifndef WIN32
	pqsignal(SIGALRM, process_alarm);
#endif
#ifdef SIGHUP
	/* Not defined on win32 */
	pqsignal(SIGHUP, signal_cleanup);
#endif

	prepare_buf();

	test_open();

	/* Test using 1 XLOG_BLCKSZ write */
	test_sync(1);

	/* Test using 2 XLOG_BLCKSZ writes */
	test_sync(2);

	test_open_syncs();

	test_file_descriptor_sync();

	test_non_sync();

	unlink(filename);

	return 0;
}