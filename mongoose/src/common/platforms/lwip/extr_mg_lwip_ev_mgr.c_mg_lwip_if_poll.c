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
typedef  double time_t ;
struct mg_mgr {struct mg_connection* active_connections; } ;
struct TYPE_3__ {TYPE_2__* tcp; } ;
struct mg_lwip_conn_state {scalar_t__ draining_rx_chain; int /*<<< orphan*/ * rx_chain; TYPE_1__ pcb; } ;
struct mg_iface {struct mg_mgr* mgr; } ;
struct mg_connection {scalar_t__ sock; int flags; double ev_timer_time; int /*<<< orphan*/  send_mbuf; struct mg_connection* next; } ;
struct TYPE_4__ {int /*<<< orphan*/ * unsent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ INVALID_SOCKET ; 
 int MG_F_LISTENING ; 
 int MG_F_UDP ; 
 int /*<<< orphan*/  MG_SIG_CLOSE_CONN ; 
 int /*<<< orphan*/  mbuf_trim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_ev_mgr_lwip_process_signals (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_if_can_recv_cb (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_if_can_send_cb (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_if_poll (struct mg_connection*,double) ; 
 scalar_t__ mg_lwip_if_can_send (struct mg_connection*,struct mg_lwip_conn_state*) ; 
 int /*<<< orphan*/  mg_lwip_netif_run_on_tcpip (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mg_lwip_post_signal (int /*<<< orphan*/ ,struct mg_connection*) ; 
 double mg_time () ; 
 int /*<<< orphan*/  tcp_output_tcpip ; 

time_t mg_lwip_if_poll(struct mg_iface *iface, int timeout_ms) {
  struct mg_mgr *mgr = iface->mgr;
  int n = 0;
  double now = mg_time();
  struct mg_connection *nc, *tmp;
  double min_timer = 0;
  int num_timers = 0;
#if 0
  DBG(("begin poll @%u", (unsigned int) (now * 1000)));
#endif
  mg_ev_mgr_lwip_process_signals(mgr);
  for (nc = mgr->active_connections; nc != NULL; nc = tmp) {
    struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
    tmp = nc->next;
    n++;
    if (!mg_if_poll(nc, now)) continue;
    if (nc->sock != INVALID_SOCKET &&
        !(nc->flags & (MG_F_UDP | MG_F_LISTENING)) && cs->pcb.tcp != NULL &&
        cs->pcb.tcp->unsent != NULL) {
      mg_lwip_netif_run_on_tcpip(tcp_output_tcpip, cs->pcb.tcp);
    }
    if (nc->ev_timer_time > 0) {
      if (num_timers == 0 || nc->ev_timer_time < min_timer) {
        min_timer = nc->ev_timer_time;
      }
      num_timers++;
    }

    if (nc->sock != INVALID_SOCKET) {
      if (mg_lwip_if_can_send(nc, cs)) {
        mg_if_can_send_cb(nc);
        mbuf_trim(&nc->send_mbuf);
      }
      if (cs->rx_chain != NULL) {
        mg_if_can_recv_cb(nc);
      } else if (cs->draining_rx_chain) {
        /*
         * If the connection is about to close, and rx_chain is finally empty,
         * send the MG_SIG_CLOSE_CONN signal
         */
        mg_lwip_post_signal(MG_SIG_CLOSE_CONN, nc);
      }
    }
  }
#if 0
  DBG(("end poll @%u, %d conns, %d timers (min %u), next in %d ms",
       (unsigned int) (now * 1000), n, num_timers,
       (unsigned int) (min_timer * 1000), timeout_ms));
#endif
  (void) timeout_ms;
  return now;
}