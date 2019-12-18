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
struct mg_mgr {TYPE_1__** ifaces; } ;
struct mg_lwip_conn_state {int /*<<< orphan*/  recv_pending; int /*<<< orphan*/  err; } ;
struct mg_ev_mgr_lwip_data {scalar_t__ sig_queue_len; int start_index; TYPE_2__* sig_queue; } ;
struct mg_connection {int /*<<< orphan*/  recv_mbuf; int /*<<< orphan*/ * mgr; int /*<<< orphan*/ * iface; scalar_t__ sock; } ;
struct TYPE_4__ {int sig; struct mg_connection* nc; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 size_t MG_MAIN_IFACE ; 
#define  MG_SIG_ACCEPT 132 
#define  MG_SIG_CLOSE_CONN 131 
#define  MG_SIG_CONNECT_RESULT 130 
 int MG_SIG_QUEUE_LEN ; 
#define  MG_SIG_RECV 129 
#define  MG_SIG_TOMBSTONE 128 
 int /*<<< orphan*/  mbuf_trim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_close_conn (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_if_can_recv_cb (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_if_connect_cb (struct mg_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_lwip_handle_accept (struct mg_connection*) ; 
 int /*<<< orphan*/  mgos_lock () ; 
 int /*<<< orphan*/  mgos_unlock () ; 

void mg_ev_mgr_lwip_process_signals(struct mg_mgr *mgr) {
  struct mg_ev_mgr_lwip_data *md =
      (struct mg_ev_mgr_lwip_data *) mgr->ifaces[MG_MAIN_IFACE]->data;
  while (md->sig_queue_len > 0) {
    mgos_lock();
    int i = md->start_index;
    int sig = md->sig_queue[i].sig;
    struct mg_connection *nc = md->sig_queue[i].nc;
    struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
    md->start_index = (i + 1) % MG_SIG_QUEUE_LEN;
    md->sig_queue_len--;
    mgos_unlock();
    if (nc->iface == NULL || nc->mgr == NULL) continue;
    switch (sig) {
      case MG_SIG_CONNECT_RESULT: {
        mg_if_connect_cb(nc, cs->err);
        break;
      }
      case MG_SIG_CLOSE_CONN: {
        mg_close_conn(nc);
        break;
      }
      case MG_SIG_RECV: {
        cs->recv_pending = 0;
        mg_if_can_recv_cb(nc);
        mbuf_trim(&nc->recv_mbuf);
        break;
      }
      case MG_SIG_TOMBSTONE: {
        break;
      }
      case MG_SIG_ACCEPT: {
        mg_lwip_handle_accept(nc);
        break;
      }
    }
  }
}