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
struct websocket_message {size_t size; char* data; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int MG_EV_WEBSOCKET_FRAME ; 
 int /*<<< orphan*/  WEBSOCKET_OP_TEXT ; 
 int /*<<< orphan*/  mg_printf_websocket_frame (struct mg_connection*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void cb3_big(struct mg_connection *nc, int ev, void *ev_data) {
  struct websocket_message *wm = (struct websocket_message *) ev_data;

  if (ev == MG_EV_WEBSOCKET_FRAME) {
    int success = 1;
    size_t i;
    for (i = 0; i < wm->size; i++) {
      if (wm->data[i] != 'x') {
        success = 0;
        break;
      }
    }
    mg_printf_websocket_frame(nc, WEBSOCKET_OP_TEXT, "%s",
                              success ? "success" : "fail");
  }
}