#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_7__ {int /*<<< orphan*/  sock; TYPE_1__* server; } ;
typedef  TYPE_2__ php_cli_server_client ;
struct TYPE_6__ {int /*<<< orphan*/  poller; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 TYPE_2__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pefree (TYPE_2__*,int) ; 
 int /*<<< orphan*/  php_cli_server_client_dtor (TYPE_2__*) ; 
 int /*<<< orphan*/  php_cli_server_poller_remove (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_cli_server_client_dtor_wrapper(zval *zv) /* {{{ */
{
	php_cli_server_client *p = Z_PTR_P(zv);

	shutdown(p->sock, SHUT_RDWR);
	closesocket(p->sock);
	php_cli_server_poller_remove(&p->server->poller, POLLIN | POLLOUT, p->sock);
	php_cli_server_client_dtor(p);
	pefree(p, 1);
}