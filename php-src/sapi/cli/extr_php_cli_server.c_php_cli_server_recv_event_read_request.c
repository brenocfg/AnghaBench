#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ request_method; } ;
struct TYPE_14__ {scalar_t__ state; } ;
struct TYPE_16__ {int /*<<< orphan*/  sock; TYPE_2__ request; int /*<<< orphan*/  addr_str; TYPE_1__ parser; } ;
typedef  TYPE_3__ php_cli_server_client ;
struct TYPE_17__ {int /*<<< orphan*/  poller; } ;
typedef  TYPE_4__ php_cli_server ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  PHP_CLI_SERVER_LOG_ERROR ; 
 int /*<<< orphan*/  PHP_CLI_SERVER_LOG_MESSAGE ; 
 scalar_t__ PHP_HTTP_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  POLLIN ; 
 int SUCCESS ; 
 int /*<<< orphan*/  efree (char*) ; 
 int php_cli_server_client_read_request (TYPE_3__*,char**) ; 
 int /*<<< orphan*/  php_cli_server_close_connection (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  php_cli_server_dispatch (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  php_cli_server_logf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  php_cli_server_poller_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_cli_server_poller_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_cli_server_request_error_unexpected_eof ; 
 int php_cli_server_send_error_page (TYPE_4__*,TYPE_3__*,int) ; 
 scalar_t__ s_start_req ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_cli_server_recv_event_read_request(php_cli_server *server, php_cli_server_client *client) /* {{{ */
{
	char *errstr = NULL;
	int status = php_cli_server_client_read_request(client, &errstr);
	if (status < 0) {
		if (errstr) {
			if (strcmp(errstr, php_cli_server_request_error_unexpected_eof) == 0 && client->parser.state == s_start_req) {
				php_cli_server_logf(PHP_CLI_SERVER_LOG_MESSAGE,
					"%s Closed without sending a request; it was probably just an unused speculative preconnection", client->addr_str);
			} else {
				php_cli_server_logf(PHP_CLI_SERVER_LOG_ERROR, "%s Invalid request (%s)", client->addr_str, errstr);
			}
			efree(errstr);
		}
		php_cli_server_close_connection(server, client);
		return FAILURE;
	} else if (status == 1 && client->request.request_method == PHP_HTTP_NOT_IMPLEMENTED) {
		return php_cli_server_send_error_page(server, client, 501);
	} else if (status == 1) {
		php_cli_server_poller_remove(&server->poller, POLLIN, client->sock);
		php_cli_server_dispatch(server, client);
	} else {
		php_cli_server_poller_add(&server->poller, POLLIN, client->sock);
	}

	return SUCCESS;
}