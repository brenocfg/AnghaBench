#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_bool ;
struct TYPE_5__ {int /*<<< orphan*/  request_uri; } ;
struct TYPE_6__ {TYPE_1__ request; int /*<<< orphan*/  addr_str; } ;
typedef  TYPE_2__ php_cli_server_client ;
struct TYPE_7__ {int /*<<< orphan*/  request_method; } ;

/* Variables and functions */
 scalar_t__ CLI_SERVER_G (int) ; 
#define  E_COMPILE_ERROR 132 
#define  E_CORE_ERROR 131 
#define  E_ERROR 130 
#define  E_PARSE 129 
#define  E_USER_ERROR 128 
 scalar_t__ OUTPUT_IS_TTY ; 
 int PG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_CLI_SERVER_LOG_MESSAGE ; 
 TYPE_4__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  last_error_file ; 
 int /*<<< orphan*/  last_error_lineno ; 
 int /*<<< orphan*/  last_error_message ; 
 int /*<<< orphan*/  last_error_type ; 
 scalar_t__ php_cli_is_output_tty () ; 
 int /*<<< orphan*/  php_cli_server_logf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  request_info ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void php_cli_server_log_response(php_cli_server_client *client, int status, const char *message) /* {{{ */
{
	int color = 0, effective_status = status;
	char *basic_buf, *message_buf = "", *error_buf = "";
	zend_bool append_error_message = 0;

	if (PG(last_error_message)) {
		switch (PG(last_error_type)) {
			case E_ERROR:
			case E_CORE_ERROR:
			case E_COMPILE_ERROR:
			case E_USER_ERROR:
			case E_PARSE:
				if (status == 200) {
					/* the status code isn't changed by a fatal error, so fake it */
					effective_status = 500;
				}

				append_error_message = 1;
				break;
		}
	}

#if HAVE_UNISTD_H
	if (CLI_SERVER_G(color) && php_cli_is_output_tty() == OUTPUT_IS_TTY) {
		if (effective_status >= 500) {
			/* server error: red */
			color = 1;
		} else if (effective_status >= 400) {
			/* client error: yellow */
			color = 3;
		} else if (effective_status >= 200) {
			/* success: green */
			color = 2;
		}
	}
#endif

	/* basic */
	spprintf(&basic_buf, 0, "%s [%d]: %s %s", client->addr_str, status, SG(request_info).request_method, client->request.request_uri);
	if (!basic_buf) {
		return;
	}

	/* message */
	if (message) {
		spprintf(&message_buf, 0, " - %s", message);
		if (!message_buf) {
			efree(basic_buf);
			return;
		}
	}

	/* error */
	if (append_error_message) {
		spprintf(&error_buf, 0, " - %s in %s on line %d", PG(last_error_message), PG(last_error_file), PG(last_error_lineno));
		if (!error_buf) {
			efree(basic_buf);
			if (message) {
				efree(message_buf);
			}
			return;
		}
	}

	if (color) {
		php_cli_server_logf(PHP_CLI_SERVER_LOG_MESSAGE, "\x1b[3%dm%s%s%s\x1b[0m", color, basic_buf, message_buf, error_buf);
	} else {
		php_cli_server_logf(PHP_CLI_SERVER_LOG_MESSAGE, "%s%s%s", basic_buf, message_buf, error_buf);
	}

	efree(basic_buf);
	if (message) {
		efree(message_buf);
	}
	if (append_error_message) {
		efree(error_buf);
	}
}