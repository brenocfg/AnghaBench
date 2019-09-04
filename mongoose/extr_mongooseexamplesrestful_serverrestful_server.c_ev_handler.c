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
struct mg_connection {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  p; } ;
struct http_message {TYPE_1__ body; int /*<<< orphan*/  uri; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  MG_EV_HTTP_REQUEST 128 
 int /*<<< orphan*/  handle_sum_call (struct mg_connection*,struct http_message*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_serve_http (struct mg_connection*,struct http_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_vcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  s_http_server_opts ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      if (mg_vcmp(&hm->uri, "/api/v1/sum") == 0) {
        handle_sum_call(nc, hm); /* Handle RESTful call */
      } else if (mg_vcmp(&hm->uri, "/printcontent") == 0) {
        char buf[100] = {0};
        memcpy(buf, hm->body.p,
               sizeof(buf) - 1 < hm->body.len ? sizeof(buf) - 1 : hm->body.len);
        printf("%s\n", buf);
      } else {
        mg_serve_http(nc, hm, s_http_server_opts); /* Serve static content */
      }
      break;
    default:
      break;
  }
}