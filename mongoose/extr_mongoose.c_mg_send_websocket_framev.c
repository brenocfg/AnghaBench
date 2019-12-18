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
struct ws_mask_ctx {int dummy; } ;
struct mg_str {scalar_t__ len; int /*<<< orphan*/  p; } ;
struct mg_connection {int /*<<< orphan*/  flags; int /*<<< orphan*/  send_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int WEBSOCKET_OP_CLOSE ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mg_send_ws_header (struct mg_connection*,int,int,struct ws_mask_ctx*) ; 
 int /*<<< orphan*/  mg_ws_mask_frame (int /*<<< orphan*/ *,struct ws_mask_ctx*) ; 

void mg_send_websocket_framev(struct mg_connection *nc, int op,
                              const struct mg_str *strv, int strvcnt) {
  struct ws_mask_ctx ctx;
  int i;
  int len = 0;
  for (i = 0; i < strvcnt; i++) {
    len += strv[i].len;
  }

  mg_send_ws_header(nc, op, len, &ctx);

  for (i = 0; i < strvcnt; i++) {
    mg_send(nc, strv[i].p, strv[i].len);
  }

  mg_ws_mask_frame(&nc->send_mbuf, &ctx);

  if (op == WEBSOCKET_OP_CLOSE) {
    nc->flags |= MG_F_SEND_AND_CLOSE;
  }
}