#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_bool ;
struct TYPE_4__ {int request_uri; } ;
struct TYPE_5__ {int addr_str; TYPE_1__ request; } ;
typedef  TYPE_2__ php_cli_server_client ;

/* Variables and functions */
#define  E_COMPILE_ERROR 132 
#define  E_CORE_ERROR 131 
#define  E_ERROR 130 
#define  E_PARSE 129 
#define  E_USER_ERROR 128 
 int PG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  last_error_file ; 
 int /*<<< orphan*/  last_error_lineno ; 
 int /*<<< orphan*/  last_error_message ; 
 int /*<<< orphan*/  last_error_type ; 
 int /*<<< orphan*/  php_cli_server_logf (char*,...) ; 
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
	spprintf(&basic_buf, 0, "%s [%d]: %s", client->addr_str, status, client->request.request_uri);
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
		php_cli_server_logf("\x1b[3%dm%s%s%s\x1b[0m", color, basic_buf, message_buf, error_buf);
	} else {
		php_cli_server_logf("%s%s%s", basic_buf, message_buf, error_buf);
	}

	efree(basic_buf);
	if (message) {
		efree(message_buf);
	}
	if (append_error_message) {
		efree(error_buf);
	}
}