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
struct websocket_message {int flags; } ;
struct mg_connection {int /*<<< orphan*/  user_data; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_EV_WEBSOCKET_CONTROL_FRAME ; 
 int /*<<< orphan*/  MG_EV_WEBSOCKET_FRAME ; 
 int /*<<< orphan*/  mg_call (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct websocket_message*) ; 

__attribute__((used)) static void mg_handle_incoming_websocket_frame(struct mg_connection *nc,
                                               struct websocket_message *wsm) {
  if (wsm->flags & 0x8) {
    mg_call(nc, nc->handler, nc->user_data, MG_EV_WEBSOCKET_CONTROL_FRAME, wsm);
  } else {
    mg_call(nc, nc->handler, nc->user_data, MG_EV_WEBSOCKET_FRAME, wsm);
  }
}