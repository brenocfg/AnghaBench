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
struct mbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct mg_connection {struct mbuf recv_mbuf; } ;

/* Variables and functions */
#define  MG_EV_RECV 128 
 int /*<<< orphan*/  mbuf_remove (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  struct mbuf *io = &nc->recv_mbuf;
  (void) p;

  switch (ev) {
    case MG_EV_RECV:
      mg_send(nc, io->buf, io->len);  // Echo message back
      mbuf_remove(io, io->len);       // Discard message from recv buffer
      break;
    default:
      break;
  }
}