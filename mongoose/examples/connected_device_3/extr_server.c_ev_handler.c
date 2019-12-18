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
#define  MG_EV_HTTP_REQUEST 129 
#define  MG_EV_SSI_CALL 128 
 int /*<<< orphan*/  handle_get_cpu_usage (struct mg_connection*) ; 
 int /*<<< orphan*/  handle_save (struct mg_connection*,struct http_message*) ; 
 int /*<<< orphan*/  handle_ssi_call (struct mg_connection*,void*) ; 
 int /*<<< orphan*/  mg_serve_http (struct mg_connection*,struct http_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_vcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  s_http_server_opts ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      if (mg_vcmp(&hm->uri, "/save") == 0) {
        handle_save(nc, hm);
      } else if (mg_vcmp(&hm->uri, "/get_cpu_usage") == 0) {
        handle_get_cpu_usage(nc);
      } else {
        mg_serve_http(nc, hm, s_http_server_opts);  // Serve static content
      }
      break;
    case MG_EV_SSI_CALL:
      handle_ssi_call(nc, ev_data);
      break;
    default:
      break;
  }
}