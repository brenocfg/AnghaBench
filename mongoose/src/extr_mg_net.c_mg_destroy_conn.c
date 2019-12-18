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
struct mg_connection {scalar_t__ sock; int /*<<< orphan*/  send_mbuf; int /*<<< orphan*/  recv_mbuf; int /*<<< orphan*/ * proto_data; int /*<<< orphan*/  (* proto_data_destructor ) (int /*<<< orphan*/ *) ;TYPE_1__* iface; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy_conn ) (struct mg_connection*) ;} ;
struct TYPE_3__ {TYPE_2__* vtable; } ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MG_FREE (struct mg_connection*) ; 
 int /*<<< orphan*/  mbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mg_connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_ssl_if_conn_free (struct mg_connection*) ; 
 int /*<<< orphan*/  stub1 (struct mg_connection*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void mg_destroy_conn(struct mg_connection *conn, int destroy_if) {
  if (conn->sock != INVALID_SOCKET) { /* Don't print timer-only conns */
    LOG(LL_DEBUG, ("%p 0x%lx %d", conn, conn->flags, destroy_if));
  }
  if (destroy_if) conn->iface->vtable->destroy_conn(conn);
  if (conn->proto_data != NULL && conn->proto_data_destructor != NULL) {
    conn->proto_data_destructor(conn->proto_data);
  }
#if MG_ENABLE_SSL
  mg_ssl_if_conn_free(conn);
#endif
  mbuf_free(&conn->recv_mbuf);
  mbuf_free(&conn->send_mbuf);

  memset(conn, 0, sizeof(*conn));
  MG_FREE(conn);
}