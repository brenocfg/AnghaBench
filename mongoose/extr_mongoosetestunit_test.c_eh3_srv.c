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
struct udp_res {int /*<<< orphan*/  buf_srv; } ;
struct mbuf {char* buf; int len; } ;
struct mg_connection {int flags; struct mbuf recv_mbuf; TYPE_1__* mgr; } ;
struct TYPE_2__ {scalar_t__ user_data; } ;

/* Variables and functions */
 int MG_EV_ACCEPT ; 
 int MG_EV_CLOSE ; 
 int MG_EV_POLL ; 
 int MG_EV_RECV ; 
 int MG_F_LISTENING ; 
 int MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  mbuf_append (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mbuf_remove (struct mbuf*,int) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,char*,int) ; 

__attribute__((used)) static void eh3_srv(struct mg_connection *nc, int ev, void *p) {
  struct udp_res *ur = (struct udp_res *) nc->mgr->user_data;
  struct mbuf *io = &nc->recv_mbuf;
  (void) p;

  if (nc->flags & MG_F_LISTENING) {
    if (ev != MG_EV_POLL && ev != MG_EV_CLOSE) {
      mbuf_append(&ur->buf_srv, "BUG", 3);
    }
    return;
  }

  if (ev == MG_EV_ACCEPT) {
    mbuf_append(&ur->buf_srv, "ACCEPT", 6);
  } else if (ev == MG_EV_RECV) {
    mbuf_append(&ur->buf_srv, (nc->flags & MG_F_SEND_AND_CLOSE ? "+" : "-"), 1);
    mbuf_append(&ur->buf_srv, " RECV ", 6);
    mbuf_append(&ur->buf_srv, io->buf, io->len);
    mg_send(nc, io->buf, io->len);
    mbuf_remove(io, io->len);
  } else if (ev == MG_EV_CLOSE) {
    mbuf_append(&ur->buf_srv, " CLOSE", 6);
  }
}