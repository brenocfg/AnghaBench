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
struct websocket_message {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct mg_connection {scalar_t__ user_data; } ;
struct big_payload_params {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int MG_EV_WEBSOCKET_FRAME ; 
 int MG_EV_WEBSOCKET_HANDSHAKE_DONE ; 
 int /*<<< orphan*/  WEBSOCKET_OP_CLOSE ; 
 int /*<<< orphan*/  WEBSOCKET_OP_TEXT ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_printf_websocket_frame (struct mg_connection*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mg_send_websocket_frame (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cb4_big(struct mg_connection *nc, int ev, void *ev_data) {
  struct websocket_message *wm = (struct websocket_message *) ev_data;
  struct big_payload_params *params =
      (struct big_payload_params *) nc->user_data;

  if (ev == MG_EV_WEBSOCKET_FRAME) {
    memcpy(params->buf, wm->data, wm->size);
    mg_send_websocket_frame(nc, WEBSOCKET_OP_CLOSE, NULL, 0);
  } else if (ev == MG_EV_WEBSOCKET_HANDSHAKE_DONE) {
    /* Send large payload to server. server must reply "success". */
    char *payload = (char *) malloc(params->size);
    memset(payload, 'x', params->size);
    mg_printf_websocket_frame(nc, WEBSOCKET_OP_TEXT, "%.*s", params->size,
                              payload);
    free(payload);
  }
}