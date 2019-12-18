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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int php_socket_t ;
struct TYPE_4__ {int server_sock; char* host; int port; char* document_root; size_t document_root_len; char* router; size_t router_len; int is_running; int /*<<< orphan*/  clients; int /*<<< orphan*/  poller; int /*<<< orphan*/  socklen; int /*<<< orphan*/  address_family; } ;
typedef  TYPE_1__ php_cli_server ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  PHP_CLI_SERVER_LOG_ERROR ; 
 int /*<<< orphan*/  POLLIN ; 
 int SOCK_ERR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int SUCCESS ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mime_type_map ; 
 int /*<<< orphan*/  pefree (char*,int) ; 
 char* pestrdup (char const*,int) ; 
 char* pestrndup (char const*,size_t,int) ; 
 int /*<<< orphan*/  php_cli_server_client_dtor_wrapper ; 
 int /*<<< orphan*/  php_cli_server_logf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int php_cli_server_mime_type_ctor (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_cli_server_poller_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int php_cli_server_poller_ctor (int /*<<< orphan*/ *) ; 
 int php_network_listen_socket (char*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_cli_server_ctor(php_cli_server *server, const char *addr, const char *document_root, const char *router) /* {{{ */
{
	int retval = SUCCESS;
	char *host = NULL;
	zend_string *errstr = NULL;
	char *_document_root = NULL;
	char *_router = NULL;
	int err = 0;
	int port = 3000;
	php_socket_t server_sock = SOCK_ERR;
	char *p = NULL;

	if (addr[0] == '[') {
		host = pestrdup(addr + 1, 1);
		if (!host) {
			return FAILURE;
		}
		p = strchr(host, ']');
		if (p) {
			*p++ = '\0';
			if (*p == ':') {
				port = strtol(p + 1, &p, 10);
				if (port <= 0 || port > 65535) {
					p = NULL;
				}
			} else if (*p != '\0') {
				p = NULL;
			}
		}
	} else {
		host = pestrdup(addr, 1);
		if (!host) {
			return FAILURE;
		}
		p = strchr(host, ':');
		if (p) {
			*p++ = '\0';
			port = strtol(p, &p, 10);
			if (port <= 0 || port > 65535) {
				p = NULL;
			}
		}
	}
	if (!p) {
		fprintf(stderr, "Invalid address: %s\n", addr);
		retval = FAILURE;
		goto out;
	}

	server_sock = php_network_listen_socket(host, &port, SOCK_STREAM, &server->address_family, &server->socklen, &errstr);
	if (server_sock == SOCK_ERR) {
		php_cli_server_logf(PHP_CLI_SERVER_LOG_ERROR, "Failed to listen on %s:%d (reason: %s)", host, port, errstr ? ZSTR_VAL(errstr) : "?");
		if (errstr) {
			zend_string_release_ex(errstr, 0);
		}
		retval = FAILURE;
		goto out;
	}
	server->server_sock = server_sock;

	err = php_cli_server_poller_ctor(&server->poller);
	if (SUCCESS != err) {
		goto out;
	}

	php_cli_server_poller_add(&server->poller, POLLIN, server_sock);

	server->host = host;
	server->port = port;

	zend_hash_init(&server->clients, 0, NULL, php_cli_server_client_dtor_wrapper, 1);

	{
		size_t document_root_len = strlen(document_root);
		_document_root = pestrndup(document_root, document_root_len, 1);
		if (!_document_root) {
			retval = FAILURE;
			goto out;
		}
		server->document_root = _document_root;
		server->document_root_len = document_root_len;
	}

	if (router) {
		size_t router_len = strlen(router);
		_router = pestrndup(router, router_len, 1);
		if (!_router) {
			retval = FAILURE;
			goto out;
		}
		server->router = _router;
		server->router_len = router_len;
	} else {
		server->router = NULL;
		server->router_len = 0;
	}

	if (php_cli_server_mime_type_ctor(server, mime_type_map) == FAILURE) {
		retval = FAILURE;
		goto out;
	}

	server->is_running = 1;
out:
	if (retval != SUCCESS) {
		if (host) {
			pefree(host, 1);
		}
		if (_document_root) {
			pefree(_document_root, 1);
		}
		if (_router) {
			pefree(_router, 1);
		}
		if (server_sock > -1) {
			closesocket(server_sock);
		}
	}
	return retval;
}