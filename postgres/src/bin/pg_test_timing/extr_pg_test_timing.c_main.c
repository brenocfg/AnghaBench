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
typedef  int /*<<< orphan*/  uint64 ;

/* Variables and functions */
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/  get_progname (char*) ; 
 int /*<<< orphan*/  handle_args (int,char**) ; 
 int /*<<< orphan*/  output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  set_pglocale_pgservice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_duration ; 
 int /*<<< orphan*/  test_timing (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	uint64		loop_count;

	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("pg_test_timing"));
	progname = get_progname(argv[0]);

	handle_args(argc, argv);

	loop_count = test_timing(test_duration);

	output(loop_count);

	return 0;
}