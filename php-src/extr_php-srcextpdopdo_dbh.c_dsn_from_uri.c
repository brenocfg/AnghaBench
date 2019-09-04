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
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_ERRORS ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 char* php_stream_get_line (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_stream_open_wrapper (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *dsn_from_uri(char *uri, char *buf, size_t buflen) /* {{{ */
{
	php_stream *stream;
	char *dsn = NULL;

	stream = php_stream_open_wrapper(uri, "rb", REPORT_ERRORS, NULL);
	if (stream) {
		dsn = php_stream_get_line(stream, buf, buflen, NULL);
		php_stream_close(stream);
	}
	return dsn;
}