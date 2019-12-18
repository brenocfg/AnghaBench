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
struct websocket_message {int size; int /*<<< orphan*/  data; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int MG_EV_WEBSOCKET_FRAME ; 
 int /*<<< orphan*/  WEBSOCKET_OP_TEXT ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mg_printf_websocket_frame (struct mg_connection*,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void cb3(struct mg_connection *nc, int ev, void *ev_data) {
  struct websocket_message *wm = (struct websocket_message *) ev_data;
  if (ev != MG_EV_WEBSOCKET_FRAME) return;
  DBG(("server data '%.*s'", (int) wm->size, wm->data));
  const char *reply = wm->size == 2 && !memcmp(wm->data, "hi", 2) ? "A" : "B";
  mg_printf_websocket_frame(nc, WEBSOCKET_OP_TEXT, "%s", reply);
}