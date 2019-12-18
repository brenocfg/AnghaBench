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
 scalar_t__ fcgi_is_fastcgi () ; 
 int /*<<< orphan*/  fcgi_logging ; 
 int fcgi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int /*<<< orphan*/  server_context ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void sapi_cgi_log_message(char *message, int syslog_type_int)
{
	if (fcgi_is_fastcgi() && CGIG(fcgi_logging)) {
		fcgi_request *request;

		request = (fcgi_request*) SG(server_context);
		if (request) {
			int ret, len = (int)strlen(message);
			char *buf = malloc(len+2);

			memcpy(buf, message, len);
			memcpy(buf + len, "\n", sizeof("\n"));
			ret = fcgi_write(request, FCGI_STDERR, buf, (int)(len + 1));
			free(buf);
			if (ret < 0) {
				php_handle_aborted_connection();
			}
		} else {
			fprintf(stderr, "%s\n", message);
		}
		/* ignore return code */
	} else {
		fprintf(stderr, "%s\n", message);
	}
}