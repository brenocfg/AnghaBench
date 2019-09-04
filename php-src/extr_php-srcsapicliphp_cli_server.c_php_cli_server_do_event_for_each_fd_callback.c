#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  php_socket_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* whandler ) (TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* rhandler ) (TYPE_2__*,int /*<<< orphan*/ *) ;TYPE_2__* server; } ;
typedef  TYPE_1__ php_cli_server_do_event_for_each_fd_callback_params ;
typedef  int /*<<< orphan*/  php_cli_server_client ;
struct TYPE_8__ {int socklen; int /*<<< orphan*/  clients; int /*<<< orphan*/  server_sock; } ;
typedef  TYPE_2__ php_cli_server ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int POLLIN ; 
 int POLLOUT ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZEND_VALID_SOCKET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  pefree (struct sockaddr*,int) ; 
 void* pemalloc (int,int) ; 
 scalar_t__ php_cli_server_client_ctor (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  php_cli_server_logf (char*,...) ; 
 int /*<<< orphan*/  php_cli_server_recv_event_read_request (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int php_set_sock_blocking (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_socket_errno () ; 
 char* php_socket_strerror (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_index_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_index_update_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

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
			char *errstr;
			errstr = php_socket_strerror(php_socket_errno(), NULL, 0);
			php_cli_server_logf("Failed to accept a client (reason: %s)", errstr);
			efree(errstr);
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
			php_cli_server_logf("Failed to create a new request object");
			pefree(sa, 1);
			closesocket(client_sock);
			return SUCCESS;
		}
#if PHP_DEBUG
		php_cli_server_logf("%s Accepted", client->addr_str);
#endif
		zend_hash_index_update_ptr(&server->clients, client_sock, client);
		php_cli_server_recv_event_read_request(server, client);
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