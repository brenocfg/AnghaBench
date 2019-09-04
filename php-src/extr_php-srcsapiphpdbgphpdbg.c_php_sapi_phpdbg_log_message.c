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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
#define  E_COMPILE_ERROR 137 
#define  E_CORE_ERROR 136 
#define  E_ERROR 135 
#define  E_PARSE 134 
#define  E_RECOVERABLE_ERROR 133 
#define  E_USER_ERROR 132 
 int PG (int /*<<< orphan*/ ) ; 
#define  PHPDBG_FINISH 131 
 int PHPDBG_G (int /*<<< orphan*/ ) ; 
 int PHPDBG_IN_EVAL ; 
 int PHPDBG_IS_STOPPING ; 
#define  PHPDBG_LEAVE 130 
#define  PHPDBG_NEXT 129 
 int PHPDBG_PREVENT_INTERACTIVE ; 
#define  PHPDBG_UNTIL 128 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  last_error_type ; 
 scalar_t__ phpdbg_booted ; 
 int /*<<< orphan*/  phpdbg_error (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  phpdbg_fully_started ; 
 int /*<<< orphan*/  phpdbg_interactive (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phpdbg_list_file (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* zend_get_executed_filename () ; 
 int /*<<< orphan*/  zend_get_executed_lineno () ; 
 int /*<<< orphan*/ * zend_string_init (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_sapi_phpdbg_log_message(char *message, int syslog_type_int) /* {{{ */
{
	/*
	* We must not request TSRM before being booted
	*/
	if (phpdbg_booted) {
		if (PHPDBG_G(flags) & PHPDBG_IN_EVAL) {
			phpdbg_error("eval", "msg=\"%s\"", "%s", message);
			return;
		}

		phpdbg_error("php", "msg=\"%s\"", "%s", message);

		if (PHPDBG_G(flags) & PHPDBG_PREVENT_INTERACTIVE) {
			return;
		}

		switch (PG(last_error_type)) {
			case E_ERROR:
			case E_CORE_ERROR:
			case E_COMPILE_ERROR:
			case E_USER_ERROR:
			case E_PARSE:
			case E_RECOVERABLE_ERROR: {
				const char *file_char = zend_get_executed_filename();
				zend_string *file = zend_string_init(file_char, strlen(file_char), 0);
				phpdbg_list_file(file, 3, zend_get_executed_lineno() - 1, zend_get_executed_lineno());
				zend_string_release(file);

				if (!phpdbg_fully_started) {
					return;
				}

				do {
					switch (phpdbg_interactive(1, NULL)) {
						case PHPDBG_LEAVE:
						case PHPDBG_FINISH:
						case PHPDBG_UNTIL:
						case PHPDBG_NEXT:
							return;
					}
				} while (!(PHPDBG_G(flags) & PHPDBG_IS_STOPPING));
			}
		}
	} else {
		fprintf(stdout, "%s\n", message);
	}
}