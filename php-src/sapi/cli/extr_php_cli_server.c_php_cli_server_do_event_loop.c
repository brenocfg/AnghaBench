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
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_4__ {int /*<<< orphan*/  poller; scalar_t__ is_running; } ;
typedef  TYPE_1__ php_cli_server ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ PHP_CLI_SERVER_LOG_ERROR ; 
 int SOCK_EINTR ; 
 int SUCCESS ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  php_cli_server_do_event_for_each_fd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ php_cli_server_log_level ; 
 int /*<<< orphan*/  php_cli_server_logf (scalar_t__,char*,char*) ; 
 int php_cli_server_poller_poll (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  php_cli_server_recv_event_read_request ; 
 int /*<<< orphan*/  php_cli_server_send_event ; 
 int php_socket_errno () ; 
 char* php_socket_strerror (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_cli_server_do_event_loop(php_cli_server *server) /* {{{ */
{
	int retval = SUCCESS;
	while (server->is_running) {
		struct timeval tv = { 1, 0 };
		int n = php_cli_server_poller_poll(&server->poller, &tv);
		if (n > 0) {
			php_cli_server_do_event_for_each_fd(server,
					php_cli_server_recv_event_read_request,
					php_cli_server_send_event);
		} else if (n == 0) {
			/* do nothing */
		} else {
			int err = php_socket_errno();
			if (err != SOCK_EINTR) {
				if (php_cli_server_log_level >= PHP_CLI_SERVER_LOG_ERROR) {
					char *errstr = php_socket_strerror(err, NULL, 0);
					php_cli_server_logf(PHP_CLI_SERVER_LOG_ERROR, "%s", errstr);
					efree(errstr);
				}
				retval = FAILURE;
				goto out;
			}
		}
	}
out:
	return retval;
}