#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; } ;
struct mg_connection {int flags; TYPE_2__ recv_mbuf; int /*<<< orphan*/  user_data; int /*<<< orphan*/  handler; } ;
struct TYPE_3__ {int len; } ;
struct http_message {TYPE_1__ body; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_EV_HTTP_CHUNK ; 
 int MG_F_DELETE_CHUNK ; 
 int /*<<< orphan*/  mg_call (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct http_message*) ; 

__attribute__((used)) static void deliver_chunk(struct mg_connection *c, struct http_message *hm,
                          int req_len) {
  /* Incomplete message received. Send MG_EV_HTTP_CHUNK event */
  hm->body.len = c->recv_mbuf.len - req_len;
  c->flags &= ~MG_F_DELETE_CHUNK;
  mg_call(c, c->handler, c->user_data, MG_EV_HTTP_CHUNK, hm);
  /* Delete processed data if user set MG_F_DELETE_CHUNK flag */
  if (c->flags & MG_F_DELETE_CHUNK) c->recv_mbuf.len = req_len;
}