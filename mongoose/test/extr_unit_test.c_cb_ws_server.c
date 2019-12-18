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
struct websocket_message {int /*<<< orphan*/  data; scalar_t__ size; int /*<<< orphan*/  flags; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int MG_EV_WEBSOCKET_CONTROL_FRAME ; 
 int MG_EV_WEBSOCKET_FRAME ; 
 int /*<<< orphan*/  WEBSOCKET_OP_TEXT ; 
 int /*<<< orphan*/  mg_printf_websocket_frame (struct mg_connection*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cb_ws_server(struct mg_connection *nc, int ev, void *ev_data) {
  struct websocket_message *wm = (struct websocket_message *) ev_data;

  if (ev == MG_EV_WEBSOCKET_FRAME || ev == MG_EV_WEBSOCKET_CONTROL_FRAME) {
    mg_printf_websocket_frame(
        nc, WEBSOCKET_OP_TEXT, "%s%.2x:{%.*s}",
        (ev == MG_EV_WEBSOCKET_CONTROL_FRAME ? "CONTROL:" : ""), wm->flags,
        (int) wm->size, wm->data);
  }
}