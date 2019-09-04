#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * s; } ;
struct TYPE_4__ {int /*<<< orphan*/ * auth_protocol; TYPE_1__ authentication_plugin_data; int /*<<< orphan*/ * intern_auth_plugin_data; int /*<<< orphan*/ * server_version; } ;
typedef  TYPE_2__ MYSQLND_PACKET_GREET ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void php_mysqlnd_greet_free_mem(void * _packet)
{
	MYSQLND_PACKET_GREET *p= (MYSQLND_PACKET_GREET *) _packet;
	if (p->server_version) {
		efree(p->server_version);
		p->server_version = NULL;
	}
	if (p->authentication_plugin_data.s && p->authentication_plugin_data.s != p->intern_auth_plugin_data) {
		efree(p->authentication_plugin_data.s);
		p->authentication_plugin_data.s = NULL;
	}
	if (p->auth_protocol) {
		efree(p->auth_protocol);
		p->auth_protocol = NULL;
	}
}