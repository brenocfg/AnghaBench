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
 scalar_t__ EBADF ; 
 scalar_t__ EOF ; 
 scalar_t__ errno ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void sapi_cli_flush(void *server_context) /* {{{ */
{
	/* Ignore EBADF here, it's caused by the fact that STDIN/STDOUT/STDERR streams
	 * are/could be closed before fflush() is called.
	 */
	if (fflush(stdout)==EOF && errno!=EBADF) {
#ifndef PHP_CLI_WIN32_NO_CONSOLE
		php_handle_aborted_connection();
#endif
	}
}