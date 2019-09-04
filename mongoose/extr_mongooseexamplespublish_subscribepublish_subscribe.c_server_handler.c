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
struct mg_connection {int flags; int /*<<< orphan*/  mgr; struct mbuf recv_mbuf; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int MG_EV_ACCEPT ; 
 int MG_EV_RECV ; 
 int MG_F_USER_2 ; 
 int MG_SOCK_STRINGIFY_IP ; 
 int MG_SOCK_STRINGIFY_PORT ; 
 int /*<<< orphan*/  mbuf_remove (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_next (int /*<<< orphan*/ ,struct mg_connection*) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_sock_addr_to_str (void*,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void server_handler(struct mg_connection *nc, int ev, void *p) {
  (void) p;
  if (ev == MG_EV_RECV) {
    // Push received message to all ncections
    struct mbuf *io = &nc->recv_mbuf;
    struct mg_connection *c;

    for (c = mg_next(nc->mgr, NULL); c != NULL; c = mg_next(nc->mgr, c)) {
      if (!(c->flags & MG_F_USER_2)) continue;  // Skip non-client connections
      mg_send(c, io->buf, io->len);
    }
    mbuf_remove(io, io->len);
  } else if (ev == MG_EV_ACCEPT) {
    char addr[32];
    mg_sock_addr_to_str(p, addr, sizeof(addr),
                        MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);
    printf("New client connected from %s\n", addr);
  }
}