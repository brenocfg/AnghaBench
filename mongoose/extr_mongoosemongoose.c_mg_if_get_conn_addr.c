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
typedef  union socket_address {int dummy; } socket_address ;
struct mg_connection {TYPE_2__* iface; } ;
struct TYPE_4__ {TYPE_1__* vtable; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_conn_addr ) (struct mg_connection*,int,union socket_address*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mg_connection*,int,union socket_address*) ; 

void mg_if_get_conn_addr(struct mg_connection *nc, int remote,
                         union socket_address *sa) {
  nc->iface->vtable->get_conn_addr(nc, remote, sa);
}