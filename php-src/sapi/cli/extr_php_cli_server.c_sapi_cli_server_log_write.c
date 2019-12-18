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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ php_cli_server_get_system_time (char*) ; 
 int php_cli_server_log_level ; 
 int php_cli_server_workers_max ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void sapi_cli_server_log_write(int type, char *msg) /* {{{ */
{
	char buf[52];

	if (php_cli_server_log_level < type) {
		return;
	}

	if (php_cli_server_get_system_time(buf) != 0) {
		memmove(buf, "unknown time, can't be fetched", sizeof("unknown time, can't be fetched"));
	} else {
		size_t l = strlen(buf);
		if (l > 0) {
			buf[l - 1] = '\0';
		} else {
			memmove(buf, "unknown", sizeof("unknown"));
		}
	}
#ifdef HAVE_FORK
	if (php_cli_server_workers_max > 1) {
		fprintf(stderr, "[%ld] [%s] %s\n", (long) getpid(), buf, msg);
	} else {
		fprintf(stderr, "[%s] %s\n", buf, msg);
	}
#else
	fprintf(stderr, "[%s] %s\n", buf, msg);
#endif
}