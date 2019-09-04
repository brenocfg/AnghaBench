#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_25__ {int len; char* data; } ;
struct TYPE_24__ {int len; char* data; } ;
struct TYPE_29__ {char hash; char* lowcase_key; TYPE_13__ value; TYPE_12__ key; } ;
typedef  TYPE_4__ ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_28__ {int content_length_n; scalar_t__ status_n; int /*<<< orphan*/  connection_close; scalar_t__ chunked; int /*<<< orphan*/  headers; int /*<<< orphan*/ * date; int /*<<< orphan*/ * server; } ;
struct TYPE_30__ {int keepalive; int upgrade; TYPE_3__ headers_in; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_5__ ngx_http_upstream_t ;
struct TYPE_31__ {int /*<<< orphan*/  headers_in_hash; } ;
typedef  TYPE_6__ ngx_http_upstream_main_conf_t ;
struct TYPE_32__ {scalar_t__ (* handler ) (TYPE_8__*,TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  offset; } ;
typedef  TYPE_7__ ngx_http_upstream_header_t ;
struct TYPE_26__ {scalar_t__ upgrade; } ;
struct TYPE_33__ {char header_hash; int header_name_end; int header_name_start; int header_end; int header_start; size_t lowcase_index; int lowcase_header; TYPE_2__* connection; TYPE_1__ headers_in; TYPE_5__* upstream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_34__ {scalar_t__ head; } ;
typedef  TYPE_9__ ngx_http_proxy_ctx_t ;
struct TYPE_27__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_NOT_MODIFIED ; 
 scalar_t__ NGX_HTTP_NO_CONTENT ; 
 scalar_t__ NGX_HTTP_PARSE_HEADER_DONE ; 
 scalar_t__ NGX_HTTP_SWITCHING_PROTOCOLS ; 
 scalar_t__ NGX_HTTP_UPSTREAM_INVALID_HEADER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 char ngx_hash (char,char) ; 
 TYPE_7__* ngx_hash_find (int /*<<< orphan*/ *,char,char*,int) ; 
 TYPE_9__* ngx_http_get_module_ctx (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_main_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_parse_header_line (TYPE_8__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_proxy_module ; 
 int /*<<< orphan*/  ngx_http_upstream_module ; 
 TYPE_4__* ngx_list_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_12__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,int,int) ; 
 char* ngx_pnalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_str_null (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_12__*,char*) ; 
 int /*<<< orphan*/  ngx_strlow (char*,char*,int) ; 
 scalar_t__ stub1 (TYPE_8__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_process_header(ngx_http_request_t *r)
{
    ngx_int_t                       rc;
    ngx_table_elt_t                *h;
    ngx_http_upstream_t            *u;
    ngx_http_proxy_ctx_t           *ctx;
    ngx_http_upstream_header_t     *hh;
    ngx_http_upstream_main_conf_t  *umcf;

    umcf = ngx_http_get_module_main_conf(r, ngx_http_upstream_module);

    for ( ;; ) {

        rc = ngx_http_parse_header_line(r, &r->upstream->buffer, 1);

        if (rc == NGX_OK) {

            /* a header line has been parsed successfully */

            h = ngx_list_push(&r->upstream->headers_in.headers);
            if (h == NULL) {
                return NGX_ERROR;
            }

            h->hash = r->header_hash;

            h->key.len = r->header_name_end - r->header_name_start;
            h->value.len = r->header_end - r->header_start;

            h->key.data = ngx_pnalloc(r->pool,
                               h->key.len + 1 + h->value.len + 1 + h->key.len);
            if (h->key.data == NULL) {
                h->hash = 0;
                return NGX_ERROR;
            }

            h->value.data = h->key.data + h->key.len + 1;
            h->lowcase_key = h->key.data + h->key.len + 1 + h->value.len + 1;

            ngx_memcpy(h->key.data, r->header_name_start, h->key.len);
            h->key.data[h->key.len] = '\0';
            ngx_memcpy(h->value.data, r->header_start, h->value.len);
            h->value.data[h->value.len] = '\0';

            if (h->key.len == r->lowcase_index) {
                ngx_memcpy(h->lowcase_key, r->lowcase_header, h->key.len);

            } else {
                ngx_strlow(h->lowcase_key, h->key.data, h->key.len);
            }

            hh = ngx_hash_find(&umcf->headers_in_hash, h->hash,
                               h->lowcase_key, h->key.len);

            if (hh && hh->handler(r, h, hh->offset) != NGX_OK) {
                return NGX_ERROR;
            }

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "http proxy header: \"%V: %V\"",
                           &h->key, &h->value);

            continue;
        }

        if (rc == NGX_HTTP_PARSE_HEADER_DONE) {

            /* a whole header has been parsed successfully */

            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "http proxy header done");

            /*
             * if no "Server" and "Date" in header line,
             * then add the special empty headers
             */

            if (r->upstream->headers_in.server == NULL) {
                h = ngx_list_push(&r->upstream->headers_in.headers);
                if (h == NULL) {
                    return NGX_ERROR;
                }

                h->hash = ngx_hash(ngx_hash(ngx_hash(ngx_hash(
                                    ngx_hash('s', 'e'), 'r'), 'v'), 'e'), 'r');

                ngx_str_set(&h->key, "Server");
                ngx_str_null(&h->value);
                h->lowcase_key = (u_char *) "server";
            }

            if (r->upstream->headers_in.date == NULL) {
                h = ngx_list_push(&r->upstream->headers_in.headers);
                if (h == NULL) {
                    return NGX_ERROR;
                }

                h->hash = ngx_hash(ngx_hash(ngx_hash('d', 'a'), 't'), 'e');

                ngx_str_set(&h->key, "Date");
                ngx_str_null(&h->value);
                h->lowcase_key = (u_char *) "date";
            }

            /* clear content length if response is chunked */

            u = r->upstream;

            if (u->headers_in.chunked) {
                u->headers_in.content_length_n = -1;
            }

            /*
             * set u->keepalive if response has no body; this allows to keep
             * connections alive in case of r->header_only or X-Accel-Redirect
             */

            ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_module);

            if (u->headers_in.status_n == NGX_HTTP_NO_CONTENT
                || u->headers_in.status_n == NGX_HTTP_NOT_MODIFIED
                || ctx->head
                || (!u->headers_in.chunked
                    && u->headers_in.content_length_n == 0))
            {
                u->keepalive = !u->headers_in.connection_close;
            }

            if (u->headers_in.status_n == NGX_HTTP_SWITCHING_PROTOCOLS) {
                u->keepalive = 0;

                if (r->headers_in.upgrade) {
                    u->upgrade = 1;
                }
            }

            return NGX_OK;
        }

        if (rc == NGX_AGAIN) {
            return NGX_AGAIN;
        }

        /* there was error while a header line parsing */

        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "upstream sent invalid header");

        return NGX_HTTP_UPSTREAM_INVALID_HEADER;
    }
}