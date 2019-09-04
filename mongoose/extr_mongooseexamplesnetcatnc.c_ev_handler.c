#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct websocket_message {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct mg_connection {TYPE_1__ recv_mbuf; int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
#define  MG_EV_ACCEPT 132 
#define  MG_EV_CLOSE 131 
#define  MG_EV_CONNECT 130 
#define  MG_EV_RECV 129 
#define  MG_EV_WEBSOCKET_FRAME 128 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_remove (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_start_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_is_websocket ; 
 int s_received_signal ; 
 int /*<<< orphan*/  stdio_thread_func ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  switch (ev) {
    case MG_EV_ACCEPT:
    case MG_EV_CONNECT:
      mg_start_thread(stdio_thread_func, nc->mgr);
      break;

    case MG_EV_WEBSOCKET_FRAME: {
      struct websocket_message *wm = (struct websocket_message *) p;
      fwrite(wm->data, 1, wm->size, stdout);
      break;
    }

    case MG_EV_CLOSE:
      s_received_signal = 1;
      break;

    case MG_EV_RECV:
      if (!s_is_websocket) {
        fwrite(nc->recv_mbuf.buf, 1, nc->recv_mbuf.len, stdout);
        mbuf_remove(&nc->recv_mbuf, nc->recv_mbuf.len);
      }
      break;

    default:
      break;
  }
}