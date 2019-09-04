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
struct TYPE_4__ {int /*<<< orphan*/  introspection_map; int /*<<< orphan*/  method_map; int /*<<< orphan*/  server_ptr; } ;
typedef  TYPE_1__ xmlrpc_server_data ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_ServerDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_server_data(xmlrpc_server_data *server)
{
	if (server) {
		XMLRPC_ServerDestroy(server->server_ptr);

		zval_ptr_dtor(&server->method_map);
		zval_ptr_dtor(&server->introspection_map);

		efree(server);
	}
}