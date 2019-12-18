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
struct mg_str {int dummy; } ;
struct mg_http_proto_data {struct mg_http_endpoint* endpoints; } ;
struct mg_http_endpoint {struct mg_http_endpoint* next; int /*<<< orphan*/  uri_pattern; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 struct mg_http_proto_data* mg_http_get_proto_data (struct mg_connection*) ; 
 int mg_match_prefix_n (int /*<<< orphan*/ ,struct mg_str) ; 

struct mg_http_endpoint *mg_http_get_endpoint_handler(struct mg_connection *nc,
                                                      struct mg_str *uri_path) {
  struct mg_http_proto_data *pd;
  struct mg_http_endpoint *ret = NULL;
  int matched, matched_max = 0;
  struct mg_http_endpoint *ep;

  if (nc == NULL) return NULL;

  pd = mg_http_get_proto_data(nc);

  if (pd == NULL) return NULL;

  ep = pd->endpoints;
  while (ep != NULL) {
    if ((matched = mg_match_prefix_n(ep->uri_pattern, *uri_path)) > 0) {
      if (matched > matched_max) {
        /* Looking for the longest suitable handler */
        ret = ep;
        matched_max = matched;
      }
    }

    ep = ep->next;
  }

  return ret;
}