#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int port; int /*<<< orphan*/ * path; int /*<<< orphan*/ * host; int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_1__ php_url ;
typedef  int /*<<< orphan*/  php_stream_wrapper ;
typedef  int /*<<< orphan*/  php_stream_context ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int GET_FTP_RESULT (int /*<<< orphan*/ *) ; 
 int REPORT_ERRORS ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * php_ftp_fopen_connect (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  php_url_free (TYPE_1__*) ; 
 TYPE_1__* php_url_parse (char const*) ; 
 int /*<<< orphan*/  zend_string_equals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_stream_ftp_rename(php_stream_wrapper *wrapper, const char *url_from, const char *url_to, int options, php_stream_context *context)
{
	php_stream *stream = NULL;
	php_url *resource_from = NULL, *resource_to = NULL;
	int result;
	char tmp_line[512];

	resource_from = php_url_parse(url_from);
	resource_to = php_url_parse(url_to);
	/* Must be same scheme (ftp/ftp or ftps/ftps), same host, and same port
		(or a 21/0 0/21 combination which is also "same")
	   Also require paths to/from */
	if (!resource_from ||
		!resource_to ||
		!resource_from->scheme ||
		!resource_to->scheme ||
		!zend_string_equals(resource_from->scheme, resource_to->scheme) ||
		!resource_from->host ||
		!resource_to->host ||
		!zend_string_equals(resource_from->host, resource_to->host) ||
		(resource_from->port != resource_to->port &&
		 resource_from->port * resource_to->port != 0 &&
		 resource_from->port + resource_to->port != 21) ||
		!resource_from->path ||
		!resource_to->path) {
		goto rename_errexit;
	}

	stream = php_ftp_fopen_connect(wrapper, url_from, "r", 0, NULL, context, NULL, NULL, NULL, NULL);
	if (!stream) {
		if (options & REPORT_ERRORS) {
			php_error_docref(NULL, E_WARNING, "Unable to connect to %s", ZSTR_VAL(resource_from->host));
		}
		goto rename_errexit;
	}

	/* Rename FROM */
	php_stream_printf(stream, "RNFR %s\r\n", (resource_from->path != NULL ? ZSTR_VAL(resource_from->path) : "/"));

	result = GET_FTP_RESULT(stream);
	if (result < 300 || result > 399) {
		if (options & REPORT_ERRORS) {
			php_error_docref(NULL, E_WARNING, "Error Renaming file: %s", tmp_line);
		}
		goto rename_errexit;
	}

	/* Rename TO */
	php_stream_printf(stream, "RNTO %s\r\n", (resource_to->path != NULL ? ZSTR_VAL(resource_to->path) : "/"));

	result = GET_FTP_RESULT(stream);
	if (result < 200 || result > 299) {
		if (options & REPORT_ERRORS) {
			php_error_docref(NULL, E_WARNING, "Error Renaming file: %s", tmp_line);
		}
		goto rename_errexit;
	}

	php_url_free(resource_from);
	php_url_free(resource_to);
	php_stream_close(stream);
	return 1;

rename_errexit:
	if (resource_from) {
		php_url_free(resource_from);
	}
	if (resource_to) {
		php_url_free(resource_to);
	}
	if (stream) {
		php_stream_close(stream);
	}
	return 0;
}