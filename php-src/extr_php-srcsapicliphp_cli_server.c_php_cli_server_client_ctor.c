#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  php_socket_t ;
struct TYPE_3__ {int file_fd; scalar_t__ content_sender_initialized; int /*<<< orphan*/  request; scalar_t__ post_read_offset; scalar_t__ current_header_value_len; int /*<<< orphan*/ * current_header_value; scalar_t__ current_header_name_allocated; scalar_t__ current_header_name_len; int /*<<< orphan*/ * current_header_name; int /*<<< orphan*/  last_header_element; scalar_t__ request_read; int /*<<< orphan*/  parser; int /*<<< orphan*/  addr_str_len; int /*<<< orphan*/  addr_str; int /*<<< orphan*/  addr_len; struct sockaddr* addr; int /*<<< orphan*/  sock; int /*<<< orphan*/ * server; } ;
typedef  TYPE_1__ php_cli_server_client ;
typedef  int /*<<< orphan*/  php_cli_server ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  HEADER_NONE ; 
 int /*<<< orphan*/  PHP_HTTP_REQUEST ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pestrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ php_cli_server_request_ctor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_http_parser_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_network_populate_name_from_sockaddr (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_cli_server_client_ctor(php_cli_server_client *client, php_cli_server *server, php_socket_t client_sock, struct sockaddr *addr, socklen_t addr_len) /* {{{ */
{
	client->server = server;
	client->sock = client_sock;
	client->addr = addr;
	client->addr_len = addr_len;
	{
		zend_string *addr_str = 0;

		php_network_populate_name_from_sockaddr(addr, addr_len, &addr_str, NULL, 0);
		client->addr_str = pestrndup(ZSTR_VAL(addr_str), ZSTR_LEN(addr_str), 1);
		client->addr_str_len = ZSTR_LEN(addr_str);
		zend_string_release_ex(addr_str, 0);
	}
	php_http_parser_init(&client->parser, PHP_HTTP_REQUEST);
	client->request_read = 0;

	client->last_header_element = HEADER_NONE;
	client->current_header_name = NULL;
	client->current_header_name_len = 0;
	client->current_header_name_allocated = 0;
	client->current_header_value = NULL;
	client->current_header_value_len = 0;

	client->post_read_offset = 0;
	if (FAILURE == php_cli_server_request_ctor(&client->request)) {
		return FAILURE;
	}
	client->content_sender_initialized = 0;
	client->file_fd = -1;
	return SUCCESS;
}