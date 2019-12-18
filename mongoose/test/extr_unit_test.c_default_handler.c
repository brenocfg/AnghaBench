#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mg_connection {TYPE_3__* listener; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  p; } ;
struct TYPE_8__ {int /*<<< orphan*/  p; scalar_t__ len; } ;
struct http_message {TYPE_2__ body; TYPE_1__ query_string; TYPE_4__ uri; } ;
struct TYPE_7__ {scalar_t__ user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int MG_EV_CLOSE ; 
 int MG_EV_HTTP_REQUEST ; 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mg_vcmp (TYPE_4__*,char*) ; 

__attribute__((used)) static void default_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;
  (void) ev_data;

  if (ev == MG_EV_HTTP_REQUEST) {
    if (mg_vcmp(&hm->uri, "/") == 0 || mg_vcmp(&hm->uri, "/foo") == 0) {
      mg_printf(nc, "HTTP/1.0 200 OK\r\n\r\n[%.*s%s%.*s %d]", (int) hm->uri.len,
                hm->uri.p, hm->query_string.len > 0 ? "?" : "",
                (int) hm->query_string.len, hm->query_string.p,
                (int) hm->body.len);
      nc->flags |= MG_F_SEND_AND_CLOSE;
    }
  } else if (ev == MG_EV_CLOSE) {
    if (nc->listener != NULL) {
      (*(int *) nc->listener->user_data) += 1;
      DBG(("%p == default close", nc));
    }
  }
}