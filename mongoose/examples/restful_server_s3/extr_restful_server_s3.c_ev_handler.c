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
struct mg_connection {int dummy; } ;
struct http_message {int /*<<< orphan*/  uri; } ;

/* Variables and functions */
#define  MG_EV_CLOSE 129 
#define  MG_EV_HTTP_REQUEST 128 
 int /*<<< orphan*/  handle_api_call (struct mg_connection*,struct http_message*) ; 
 int /*<<< orphan*/  mg_serve_http (struct mg_connection*,struct http_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_vcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  s_http_server_opts ; 
 int /*<<< orphan*/  unlink_conns (struct mg_connection*) ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      if (mg_vcmp(&hm->uri, "/upload") == 0) {
        handle_api_call(nc, hm); /* Handle RESTful call */
      } else {
        mg_serve_http(nc, hm, s_http_server_opts); /* Serve static content */
      }
      break;
    case MG_EV_CLOSE:
      unlink_conns(nc);
      break;
    default:
      break;
  }
}