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
struct mg_connection {TYPE_2__* iface; } ;
typedef  scalar_t__ sock_t ;
struct TYPE_4__ {TYPE_1__* vtable; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sock_set ) (struct mg_connection*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  stub1 (struct mg_connection*,scalar_t__) ; 

void mg_sock_set(struct mg_connection *nc, sock_t sock) {
  if (sock != INVALID_SOCKET) {
    nc->iface->vtable->sock_set(nc, sock);
  }
}