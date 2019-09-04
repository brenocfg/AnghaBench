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
struct mg_connection {int /*<<< orphan*/  flags; struct mbuf recv_mbuf; } ;

/* Variables and functions */
#define  MG_EV_RECV 128 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  mbuf_remove (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  struct mbuf *io = &nc->recv_mbuf;
  (void) p;
  switch (ev) {
    case MG_EV_RECV:
      mg_send(nc, io->buf, io->len);  // Echo message back
      mbuf_remove(io, io->len);       // Discard message from recv buffer
      // In case of UDP, Mongoose creates new virtual connection for
      // incoming messages
      // We can keep it (and it will be reused for another messages from
      // the same address) or we can close it (this saves some memory, but
      // decreases perfomance, because it forces creation of connection
      // for every incoming dgram)
      nc->flags |= MG_F_SEND_AND_CLOSE;
      break;
    default:
      break;
  }
}