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
struct mg_http_proto_data {scalar_t__ endpoint_handler; } ;
struct mg_http_endpoint {void* user_data; scalar_t__ handler; int /*<<< orphan*/  auth_domain; int /*<<< orphan*/  auth_file; } ;
struct mg_connection {scalar_t__ handler; int /*<<< orphan*/  listener; void* user_data; } ;
struct http_message {int /*<<< orphan*/  uri; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_AUTH_FLAG_IS_GLOBAL_PASS_FILE ; 
 int MG_EV_HTTP_MULTIPART_REQUEST ; 
 int MG_EV_HTTP_REQUEST ; 
 int /*<<< orphan*/  mg_call (struct mg_connection*,scalar_t__,void*,int,struct http_message*) ; 
 struct mg_http_endpoint* mg_http_get_endpoint_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mg_http_proto_data* mg_http_get_proto_data (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_http_is_authorized (struct http_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_http_send_digest_auth_request (struct mg_connection*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mg_http_call_endpoint_handler(struct mg_connection *nc, int ev,
                                          struct http_message *hm) {
  struct mg_http_proto_data *pd = mg_http_get_proto_data(nc);
  void *user_data = nc->user_data;

  if (ev == MG_EV_HTTP_REQUEST
#if MG_ENABLE_HTTP_STREAMING_MULTIPART
      || ev == MG_EV_HTTP_MULTIPART_REQUEST
#endif
      ) {
    struct mg_http_endpoint *ep =
        mg_http_get_endpoint_handler(nc->listener, &hm->uri);
    if (ep != NULL) {
#if MG_ENABLE_FILESYSTEM && !MG_DISABLE_HTTP_DIGEST_AUTH
      if (!mg_http_is_authorized(hm, hm->uri, ep->auth_domain, ep->auth_file,
                                 MG_AUTH_FLAG_IS_GLOBAL_PASS_FILE)) {
        mg_http_send_digest_auth_request(nc, ep->auth_domain);
        return;
      }
#endif
      pd->endpoint_handler = ep->handler;
#if MG_ENABLE_CALLBACK_USERDATA
      user_data = ep->user_data;
#endif
    }
  }
  mg_call(nc, pd->endpoint_handler ? pd->endpoint_handler : nc->handler,
          user_data, ev, hm);
}