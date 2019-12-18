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
typedef  union socket_address {int dummy; } socket_address ;
struct mg_connection {int flags; int /*<<< orphan*/  sock; int /*<<< orphan*/  sa; } ;

/* Variables and functions */
 int MG_F_UDP ; 
 int /*<<< orphan*/  memcpy (union socket_address*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mg_sock_get_addr (int /*<<< orphan*/ ,int,union socket_address*) ; 

void mg_socket_if_get_conn_addr(struct mg_connection *nc, int remote,
                                union socket_address *sa) {
  if ((nc->flags & MG_F_UDP) && remote) {
    memcpy(sa, &nc->sa, sizeof(*sa));
    return;
  }
  mg_sock_get_addr(nc->sock, remote, sa);
}