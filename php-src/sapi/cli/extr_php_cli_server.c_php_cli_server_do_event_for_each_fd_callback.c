#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  php_socket_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* whandler ) (TYPE_3__*,TYPE_2__*) ;int /*<<< orphan*/  (* rhandler ) (TYPE_3__*,TYPE_2__*) ;TYPE_3__* server; } ;
typedef  TYPE_1__ php_cli_server_do_event_for_each_fd_callback_params ;
struct TYPE_13__ {char* addr_str; int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ php_cli_server_client ;
struct TYPE_14__ {int socklen; int /*<<< orphan*/  clients; int /*<<< orphan*/  poller; int /*<<< orphan*/  server_sock; } ;
typedef  TYPE_3__ php_cli_server ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ PHP_CLI_SERVER_LOG_ERROR ; 
 scalar_t__ PHP_CLI_SERVER_LOG_MESSAGE ; 
 int POLLIN ; 
 int POLLOUT ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZEND_VALID_SOCKET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  pefree (struct sockaddr*,int) ; 
 void* pemalloc (int,int) ; 
 scalar_t__ php_cli_server_client_ctor (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ php_cli_server_log_level ; 
 int /*<<< orphan*/  php_cli_server_logf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  php_cli_server_poller_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int php_set_sock_blocking (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_socket_errno () ; 
 char* php_socket_strerror (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* zend_hash_index_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_index_update_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int php_cli_server_do_event_for_each_fd_callback(void *_params, php_socket_t fd, int event) /* {{{ */
{
	php_cli_server_do_event_for_each_fd_callback_params *params = _params;
	php_cli_server *server = params->server;
	if (server->server_sock == fd) {
		php_cli_server_client *client = NULL;
		php_socket_t client_sock;
		socklen_t socklen = server->socklen;
		struct sockaddr *sa = pemalloc(server->socklen, 1);
		client_sock = accept(server->server_sock, sa, &socklen);
		if (!ZEND_VALID_SOCKET(client_sock)) {
			if (php_cli_server_log_level >= PHP_CLI_SERVER_LOG_ERROR) {
				char *errstr = php_socket_strerror(php_socket_errno(), NULL, 0);
				php_cli_server_logf(PHP_CLI_SERVER_LOG_ERROR,
					"Failed to accept a client (reason: %s)", errstr);
				efree(errstr);
			}
			pefree(sa, 1);
			return SUCCESS;
		}
		if (SUCCESS != php_set_sock_blocking(client_sock, 0)) {
			pefree(sa, 1);
			closesocket(client_sock);
			return SUCCESS;
		}
		client = pemalloc(sizeof(php_cli_server_client), 1);
		if (FAILURE == php_cli_server_client_ctor(client, server, client_sock, sa, socklen)) {
			php_cli_server_logf(PHP_CLI_SERVER_LOG_ERROR, "Failed to create a new request object");
			pefree(sa, 1);
			closesocket(client_sock);
			return SUCCESS;
		}

		php_cli_server_logf(PHP_CLI_SERVER_LOG_MESSAGE, "%s Accepted", client->addr_str);

		zend_hash_index_update_ptr(&server->clients, client_sock, client);

		php_cli_server_poller_add(&server->poller, POLLIN, client->sock);
	} else {
		php_cli_server_client *client;
		if (NULL != (client = zend_hash_index_find_ptr(&server->clients, fd))) {
			if (event & POLLIN) {
				params->rhandler(server, client);
			}
			if (event & POLLOUT) {
				params->whandler(server, client);
			}
		}
	}
	return SUCCESS;
}