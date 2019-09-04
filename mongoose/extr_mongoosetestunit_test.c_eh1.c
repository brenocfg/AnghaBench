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
struct mbuf {int len; int /*<<< orphan*/  buf; } ;
struct mg_connection {int /*<<< orphan*/  flags; scalar_t__ user_data; int /*<<< orphan*/ * listener; struct mbuf recv_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
#define  MG_EV_CONNECT 129 
#define  MG_EV_RECV 128 
 int /*<<< orphan*/  MG_F_CLOSE_IMMEDIATELY ; 
 int /*<<< orphan*/  mbuf_remove (struct mbuf*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,int,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void eh1(struct mg_connection *nc, int ev, void *ev_data) {
  struct mbuf *io = &nc->recv_mbuf;

  switch (ev) {
    case MG_EV_CONNECT: {
      int res = *((int *) ev_data);
      if (res == 0) {
        mg_printf(nc, "%d %s there", *(int *) ev_data, "hi");
      } else {
        sprintf((char *) nc->user_data, "connect failed! %d", res);
      }
      break;
    }
    case MG_EV_RECV: {
      if (nc->listener != NULL) {
        mg_printf(nc, "%d", (int) io->len);
        mbuf_remove(io, io->len);
      } else if (io->len > 0) {
        sprintf((char *) nc->user_data, "%sok!",
                (io->len == 2 && memcmp(io->buf, "10", 2) == 0) ? "" : "NOT ");
        DBG(("%s", (const char *) nc->user_data));
        nc->flags |= MG_F_CLOSE_IMMEDIATELY;
      }
      break;
    }
    default:
      break;
  }
}