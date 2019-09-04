#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int len; char* data; } ;
struct TYPE_25__ {int len; char* data; } ;
struct TYPE_32__ {char* lowcase_key; TYPE_16__ value; TYPE_15__ key; scalar_t__ hash; } ;
typedef  TYPE_6__ ngx_table_elt_t ;
struct TYPE_33__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_31__ {int status_n; TYPE_7__ status_line; scalar_t__ location; TYPE_3__* status; int /*<<< orphan*/  headers; } ;
struct TYPE_34__ {int upgrade; TYPE_5__ headers_in; TYPE_1__* state; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_8__ ngx_http_upstream_t ;
struct TYPE_35__ {int /*<<< orphan*/  headers_in_hash; } ;
typedef  TYPE_9__ ngx_http_upstream_main_conf_t ;
struct TYPE_23__ {scalar_t__ (* handler ) (TYPE_11__*,TYPE_6__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  offset; } ;
typedef  TYPE_10__ ngx_http_upstream_header_t ;
struct TYPE_28__ {scalar_t__ upgrade; } ;
struct TYPE_24__ {int header_name_end; int header_name_start; int header_end; int header_start; size_t lowcase_index; int lowcase_header; TYPE_4__* connection; TYPE_2__ headers_in; TYPE_8__* upstream; int /*<<< orphan*/  pool; scalar_t__ header_hash; } ;
typedef  TYPE_11__ ngx_http_request_t ;
struct TYPE_30__ {int /*<<< orphan*/  log; } ;
struct TYPE_29__ {TYPE_7__ value; } ;
struct TYPE_27__ {int status; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_PARSE_HEADER_DONE ; 
 int NGX_HTTP_SWITCHING_PROTOCOLS ; 
 scalar_t__ NGX_HTTP_UPSTREAM_INVALID_HEADER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ ,int) ; 
 TYPE_10__* ngx_hash_find (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 TYPE_9__* ngx_http_get_module_main_conf (TYPE_11__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_parse_header_line (TYPE_11__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_upstream_module ; 
 TYPE_6__* ngx_list_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_15__*,TYPE_16__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,int,int) ; 
 char* ngx_pnalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  ngx_strlow (char*,char*,int) ; 
 scalar_t__ stub1 (TYPE_11__*,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_scgi_process_header(ngx_http_request_t *r)
{
    ngx_str_t                      *status_line;
    ngx_int_t                       rc, status;
    ngx_table_elt_t                *h;
    ngx_http_upstream_t            *u;
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
                                      h->key.len + 1 + h->value.len + 1
                                      + h->key.len);
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
                           "http scgi header: \"%V: %V\"", &h->key, &h->value);

            continue;
        }

        if (rc == NGX_HTTP_PARSE_HEADER_DONE) {

            /* a whole header has been parsed successfully */

            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "http scgi header done");

            u = r->upstream;

            if (u->headers_in.status_n) {
                goto done;
            }

            if (u->headers_in.status) {
                status_line = &u->headers_in.status->value;

                status = ngx_atoi(status_line->data, 3);
                if (status == NGX_ERROR) {
                    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                  "upstream sent invalid status \"%V\"",
                                  status_line);
                    return NGX_HTTP_UPSTREAM_INVALID_HEADER;
                }

                u->headers_in.status_n = status;
                u->headers_in.status_line = *status_line;

            } else if (u->headers_in.location) {
                u->headers_in.status_n = 302;
                ngx_str_set(&u->headers_in.status_line,
                            "302 Moved Temporarily");

            } else {
                u->headers_in.status_n = 200;
                ngx_str_set(&u->headers_in.status_line, "200 OK");
            }

            if (u->state && u->state->status == 0) {
                u->state->status = u->headers_in.status_n;
            }

        done:

            if (u->headers_in.status_n == NGX_HTTP_SWITCHING_PROTOCOLS
                && r->headers_in.upgrade)
            {
                u->upgrade = 1;
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