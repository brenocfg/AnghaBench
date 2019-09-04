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
struct TYPE_3__ {scalar_t__ router; scalar_t__ document_root; scalar_t__ host; int /*<<< orphan*/  server_sock; int /*<<< orphan*/  extension_mime_types; int /*<<< orphan*/  clients; } ;
typedef  TYPE_1__ php_cli_server ;

/* Variables and functions */
 scalar_t__ ZEND_VALID_SOCKET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pefree (scalar_t__,int) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_cli_server_dtor(php_cli_server *server) /* {{{ */
{
	zend_hash_destroy(&server->clients);
	zend_hash_destroy(&server->extension_mime_types);
	if (ZEND_VALID_SOCKET(server->server_sock)) {
		closesocket(server->server_sock);
	}
	if (server->host) {
		pefree(server->host, 1);
	}
	if (server->document_root) {
		pefree(server->document_root, 1);
	}
	if (server->router) {
		pefree(server->router, 1);
	}
}