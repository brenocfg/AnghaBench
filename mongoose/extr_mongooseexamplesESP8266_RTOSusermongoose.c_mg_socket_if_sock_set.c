#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mg_connection {int /*<<< orphan*/  sock; } ;
typedef  int /*<<< orphan*/  sock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  mg_set_close_on_exec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_set_non_blocking_mode (int /*<<< orphan*/ ) ; 

void mg_socket_if_sock_set(struct mg_connection *nc, sock_t sock) {
  mg_set_non_blocking_mode(sock);
  mg_set_close_on_exec(sock);
  nc->sock = sock;
  DBG(("%p %d", nc, sock));
}