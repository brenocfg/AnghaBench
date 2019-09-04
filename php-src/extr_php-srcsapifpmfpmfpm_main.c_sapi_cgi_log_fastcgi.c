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
typedef  int /*<<< orphan*/  fcgi_request ;

/* Variables and functions */
 scalar_t__ CGIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCGI_STDERR ; 
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcgi_logging ; 
 scalar_t__ fcgi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int /*<<< orphan*/  server_context ; 

void sapi_cgi_log_fastcgi(int level, char *message, size_t len)
{

	fcgi_request *request = (fcgi_request*) SG(server_context);

	/* message is written to FCGI_STDERR if following conditions are met:
	 * - logging is enabled (fastcgi.logging in php.ini)
	 * - we are currently dealing with a request
	 * - the message is not empty
	 * - the fcgi_write did not fail
	 */
	if (CGIG(fcgi_logging) && request && message && len > 0
			&& fcgi_write(request, FCGI_STDERR, message, len) < 0) {
		php_handle_aborted_connection();
	}
}