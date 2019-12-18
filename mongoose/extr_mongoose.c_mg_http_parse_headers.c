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
struct mg_str {int len; char* p; } ;
struct TYPE_4__ {size_t len; } ;
struct TYPE_3__ {int len; } ;
struct http_message {TYPE_2__ body; TYPE_1__ message; struct mg_str* header_values; struct mg_str* header_names; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct mg_str*) ; 
 int /*<<< orphan*/  mg_ncasecmp (char*,char*,int) ; 
 char* mg_skip (char const*,char const*,char*,struct mg_str*) ; 
 scalar_t__ to64 (char*) ; 

__attribute__((used)) static const char *mg_http_parse_headers(const char *s, const char *end,
                                         int len, struct http_message *req) {
  int i = 0;
  while (i < (int) ARRAY_SIZE(req->header_names) - 1) {
    struct mg_str *k = &req->header_names[i], *v = &req->header_values[i];

    s = mg_skip(s, end, ": ", k);
    s = mg_skip(s, end, "\r\n", v);

    while (v->len > 0 && v->p[v->len - 1] == ' ') {
      v->len--; /* Trim trailing spaces in header value */
    }

    /*
     * If header value is empty - skip it and go to next (if any).
     * NOTE: Do not add it to headers_values because such addition changes API
     * behaviour
     */
    if (k->len != 0 && v->len == 0) {
      continue;
    }

    if (k->len == 0 || v->len == 0) {
      k->p = v->p = NULL;
      k->len = v->len = 0;
      break;
    }

    if (!mg_ncasecmp(k->p, "Content-Length", 14)) {
      req->body.len = (size_t) to64(v->p);
      req->message.len = len + req->body.len;
    }

    i++;
  }

  return s;
}