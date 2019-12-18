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
struct mg_connection {int flags; scalar_t__ user_data; struct mbuf recv_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int MG_EV_CLOSE ; 
 int MG_EV_CONNECT ; 
 int MG_EV_RECV ; 
 int MG_F_CLOSE_IMMEDIATELY ; 
 int MG_F_USER_1 ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_remove (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void client_handler(struct mg_connection *conn, int ev, void *p) {
  struct mbuf *io = &conn->recv_mbuf;
  (void) p;

  if (ev == MG_EV_CONNECT) {
    if (conn->flags & MG_F_CLOSE_IMMEDIATELY) {
      printf("%s\n", "Error connecting to server!");
      exit(EXIT_FAILURE);
    }
    printf("%s\n", "Connected to server. Type a message and press enter.");
  } else if (ev == MG_EV_RECV) {
    if (conn->flags & MG_F_USER_1) {
      // Received data from the stdin, forward it to the server
      struct mg_connection *c = (struct mg_connection *) conn->user_data;
      mg_send(c, io->buf, io->len);
      mbuf_remove(io, io->len);
    } else {
      // Received data from server connection, print it
      fwrite(io->buf, io->len, 1, stdout);
      mbuf_remove(io, io->len);
    }
  } else if (ev == MG_EV_CLOSE) {
    // Connection has closed, most probably cause server has stopped
    exit(EXIT_SUCCESS);
  }
}