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
struct mg_connection {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  WEBSOCKET_OP_CLOSE ; 
 int /*<<< orphan*/  mg_send_websocket_frame (struct mg_connection*,int /*<<< orphan*/ ,void const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void mg_ws_close(struct mg_connection *nc, const void *data,
                        size_t len) {
  if ((int) len == ~0) {
    len = strlen((const char *) data);
  }
  mg_send_websocket_frame(nc, WEBSOCKET_OP_CLOSE, data, len);
  nc->flags |= MG_F_SEND_AND_CLOSE;
}