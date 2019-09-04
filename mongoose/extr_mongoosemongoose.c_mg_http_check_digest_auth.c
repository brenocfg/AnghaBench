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
typedef  int /*<<< orphan*/  username_buf ;
typedef  int /*<<< orphan*/  uri_buf ;
struct mg_str {int dummy; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  p; } ;
struct http_message {TYPE_2__ query_string; TYPE_1__ uri; int /*<<< orphan*/  method; } ;
typedef  int /*<<< orphan*/  response_buf ;
typedef  int /*<<< orphan*/  qop_buf ;
typedef  int /*<<< orphan*/  nonce_buf ;
typedef  int /*<<< orphan*/  nc_buf ;
typedef  int /*<<< orphan*/  cnonce_buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MG_FREE (char*) ; 
 int mg_check_digest_auth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mg_check_nonce (char*) ; 
 struct mg_str* mg_get_http_header (struct http_message*,char*) ; 
 scalar_t__ mg_http_parse_header2 (struct mg_str*,char*,char**,int) ; 
 int /*<<< orphan*/  mg_mk_str (char const*) ; 
 int /*<<< orphan*/  mg_mk_str_n (int /*<<< orphan*/ ,scalar_t__) ; 

int mg_http_check_digest_auth(struct http_message *hm, const char *auth_domain,
                              FILE *fp) {
  int ret = 0;
  struct mg_str *hdr;
  char username_buf[50], cnonce_buf[64], response_buf[40], uri_buf[200],
      qop_buf[20], nc_buf[20], nonce_buf[16];

  char *username = username_buf, *cnonce = cnonce_buf, *response = response_buf,
       *uri = uri_buf, *qop = qop_buf, *nc = nc_buf, *nonce = nonce_buf;

  /* Parse "Authorization:" header, fail fast on parse error */
  if (hm == NULL || fp == NULL ||
      (hdr = mg_get_http_header(hm, "Authorization")) == NULL ||
      mg_http_parse_header2(hdr, "username", &username, sizeof(username_buf)) ==
          0 ||
      mg_http_parse_header2(hdr, "cnonce", &cnonce, sizeof(cnonce_buf)) == 0 ||
      mg_http_parse_header2(hdr, "response", &response, sizeof(response_buf)) ==
          0 ||
      mg_http_parse_header2(hdr, "uri", &uri, sizeof(uri_buf)) == 0 ||
      mg_http_parse_header2(hdr, "qop", &qop, sizeof(qop_buf)) == 0 ||
      mg_http_parse_header2(hdr, "nc", &nc, sizeof(nc_buf)) == 0 ||
      mg_http_parse_header2(hdr, "nonce", &nonce, sizeof(nonce_buf)) == 0 ||
      mg_check_nonce(nonce) == 0) {
    ret = 0;
    goto clean;
  }

  /* NOTE(lsm): due to a bug in MSIE, we do not compare URIs */

  ret = mg_check_digest_auth(
      hm->method,
      mg_mk_str_n(
          hm->uri.p,
          hm->uri.len + (hm->query_string.len ? hm->query_string.len + 1 : 0)),
      mg_mk_str(username), mg_mk_str(cnonce), mg_mk_str(response),
      mg_mk_str(qop), mg_mk_str(nc), mg_mk_str(nonce), mg_mk_str(auth_domain),
      fp);

clean:
  if (username != username_buf) MG_FREE(username);
  if (cnonce != cnonce_buf) MG_FREE(cnonce);
  if (response != response_buf) MG_FREE(response);
  if (uri != uri_buf) MG_FREE(uri);
  if (qop != qop_buf) MG_FREE(qop);
  if (nc != nc_buf) MG_FREE(nc);
  if (nonce != nonce_buf) MG_FREE(nonce);

  return ret;
}