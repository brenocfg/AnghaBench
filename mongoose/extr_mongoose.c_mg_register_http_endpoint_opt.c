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
struct mg_http_proto_data {struct mg_http_endpoint* endpoints; } ;
struct mg_http_endpoint_opts {int /*<<< orphan*/  user_data; int /*<<< orphan*/ * auth_file; int /*<<< orphan*/ * auth_domain; } ;
struct mg_http_endpoint {struct mg_http_endpoint* next; int /*<<< orphan*/  user_data; int /*<<< orphan*/  handler; void* auth_file; void* auth_domain; int /*<<< orphan*/  uri_pattern; } ;
struct mg_connection {int dummy; } ;
typedef  int /*<<< orphan*/  mg_event_handler_t ;

/* Variables and functions */
 scalar_t__ MG_CALLOC (int,int) ; 
 struct mg_http_proto_data* mg_http_create_proto_data (struct mg_connection*) ; 
 struct mg_http_proto_data* mg_http_get_proto_data (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_mk_str (char const*) ; 
 int /*<<< orphan*/  mg_strdup (int /*<<< orphan*/ ) ; 
 void* strdup (int /*<<< orphan*/ *) ; 

void mg_register_http_endpoint_opt(struct mg_connection *nc,
                                   const char *uri_path,
                                   mg_event_handler_t handler,
                                   struct mg_http_endpoint_opts opts) {
  struct mg_http_proto_data *pd = NULL;
  struct mg_http_endpoint *new_ep = NULL;

  if (nc == NULL) return;
  new_ep = (struct mg_http_endpoint *) MG_CALLOC(1, sizeof(*new_ep));
  if (new_ep == NULL) return;

  pd = mg_http_get_proto_data(nc);
  if (pd == NULL) pd = mg_http_create_proto_data(nc);
  new_ep->uri_pattern = mg_strdup(mg_mk_str(uri_path));
  if (opts.auth_domain != NULL && opts.auth_file != NULL) {
    new_ep->auth_domain = strdup(opts.auth_domain);
    new_ep->auth_file = strdup(opts.auth_file);
  }
  new_ep->handler = handler;
#if MG_ENABLE_CALLBACK_USERDATA
  new_ep->user_data = opts.user_data;
#endif
  new_ep->next = pd->endpoints;
  pd->endpoints = new_ep;
}