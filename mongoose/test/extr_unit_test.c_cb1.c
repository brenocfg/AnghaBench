#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  p; scalar_t__ len; } ;
struct TYPE_12__ {int /*<<< orphan*/  p; scalar_t__ len; } ;
struct mg_ssi_call_ctx {TYPE_5__ arg; TYPE_4__ file; TYPE_3__* req; } ;
struct mg_connection {int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_15__ {int /*<<< orphan*/  p; scalar_t__ len; } ;
struct http_message {TYPE_1__ body; TYPE_7__ uri; } ;
struct TYPE_14__ {char* document_root; char* per_directory_auth_file; char* auth_domain; char* dav_document_root; char* hidden_file_pattern; char* custom_mime_types; } ;
struct TYPE_10__ {int /*<<< orphan*/  p; scalar_t__ len; } ;
struct TYPE_11__ {TYPE_2__ uri; } ;

/* Variables and functions */
 int MG_EV_HTTP_REQUEST ; 
 int MG_EV_SSI_CALL ; 
 int MG_EV_SSI_CALL_CTX ; 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_printf_html_escape (struct mg_connection*,char*,...) ; 
 int /*<<< orphan*/  mg_serve_http (struct mg_connection*,struct http_message*,TYPE_6__) ; 
 scalar_t__ mg_vcmp (TYPE_7__*,char*) ; 
 TYPE_6__ s_http_server_opts ; 

__attribute__((used)) static void cb1(struct mg_connection *nc, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_REQUEST) {
    struct http_message *hm = (struct http_message *) ev_data;
    if (mg_vcmp(&hm->uri, "/foo") == 0) {
      mg_printf(nc, "HTTP/1.0 200 OK\r\n\r\n[%.*s %d]", (int) hm->uri.len,
                hm->uri.p, (int) hm->body.len);
      nc->flags |= MG_F_SEND_AND_CLOSE;
    } else {
      s_http_server_opts.document_root = ".";
      s_http_server_opts.per_directory_auth_file = "passwords.txt";
      s_http_server_opts.auth_domain = "foo.com";
      s_http_server_opts.dav_document_root = "./data/dav";
      s_http_server_opts.hidden_file_pattern = "hidden_file.*$";
      s_http_server_opts.custom_mime_types =
          ".txt=text/plain; charset=windows-1251,"
          ".c=text/plain; charset=utf-8";
      mg_serve_http(nc, hm, s_http_server_opts);
    }
  } else if (ev == MG_EV_SSI_CALL) {
    mg_printf_html_escape(nc, "[ssi call: %s]", (char *) ev_data);
  } else if (ev == MG_EV_SSI_CALL_CTX) {
    struct mg_ssi_call_ctx *cctx = (struct mg_ssi_call_ctx *) ev_data;
    mg_printf_html_escape(nc, "[ssi call w/ ctx: %.*s %.*s %.*s]",
                          (int) cctx->req->uri.len, cctx->req->uri.p,
                          (int) cctx->file.len, cctx->file.p,
                          (int) cctx->arg.len, cctx->arg.p);
  }
}