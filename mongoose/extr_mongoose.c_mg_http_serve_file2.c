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
struct mg_serve_http_opts {int /*<<< orphan*/  extra_headers; int /*<<< orphan*/  ssi_pattern; } ;
struct mg_connection {int dummy; } ;
struct http_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_get_mime_type (char const*,char*,struct mg_serve_http_opts*) ; 
 int /*<<< orphan*/  mg_handle_ssi_request (struct mg_connection*,struct http_message*,char const*,struct mg_serve_http_opts*) ; 
 int /*<<< orphan*/  mg_http_serve_file (struct mg_connection*,struct http_message*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mg_match_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mg_mk_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mg_http_serve_file2(struct mg_connection *nc, const char *path,
                                struct http_message *hm,
                                struct mg_serve_http_opts *opts) {
#if MG_ENABLE_HTTP_SSI
  if (mg_match_prefix(opts->ssi_pattern, strlen(opts->ssi_pattern), path) > 0) {
    mg_handle_ssi_request(nc, hm, path, opts);
    return;
  }
#endif
  mg_http_serve_file(nc, hm, path, mg_get_mime_type(path, "text/plain", opts),
                     mg_mk_str(opts->extra_headers));
}