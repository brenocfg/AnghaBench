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
struct TYPE_3__ {int file_fd; int /*<<< orphan*/  content_sender; scalar_t__ content_sender_initialized; int /*<<< orphan*/  addr_str; int /*<<< orphan*/  addr; int /*<<< orphan*/  request; } ;
typedef  TYPE_1__ php_cli_server_client ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  pefree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_cli_server_content_sender_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_cli_server_request_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_cli_server_client_dtor(php_cli_server_client *client) /* {{{ */
{
	php_cli_server_request_dtor(&client->request);
	if (client->file_fd >= 0) {
		close(client->file_fd);
		client->file_fd = -1;
	}
	pefree(client->addr, 1);
	pefree(client->addr_str, 1);
	if (client->content_sender_initialized) {
		php_cli_server_content_sender_dtor(&client->content_sender);
	}
}