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
struct TYPE_2__ {scalar_t__ len; } ;
struct mg_connection {int /*<<< orphan*/  flags; TYPE_1__ send_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_F_CLOSE_IMMEDIATELY ; 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  WEBSOCKET_OP_TEXT ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,unsigned char*,int) ; 
 int /*<<< orphan*/  mg_send_websocket_frame (struct mg_connection*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ s_is_websocket ; 

__attribute__((used)) static void on_stdin_read(struct mg_connection *nc, int ev, void *p) {
  int ch = *(int *) p;

  (void) ev;

  if (ch < 0) {
    // EOF is received from stdin. Schedule the connection to close
    nc->flags |= MG_F_SEND_AND_CLOSE;
    if (nc->send_mbuf.len <= 0) {
      nc->flags |= MG_F_CLOSE_IMMEDIATELY;
    }
  } else {
    // A character is received from stdin. Send it to the connection.
    unsigned char c = (unsigned char) ch;
    if (s_is_websocket) {
      mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, &c, 1);
    } else {
      mg_send(nc, &c, 1);
    }
  }
}