#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_17__ ;
typedef  struct TYPE_47__   TYPE_16__ ;
typedef  struct TYPE_46__   TYPE_15__ ;
typedef  struct TYPE_45__   TYPE_14__ ;
typedef  struct TYPE_44__   TYPE_13__ ;
typedef  struct TYPE_43__   TYPE_12__ ;
typedef  struct TYPE_42__   TYPE_11__ ;
typedef  struct TYPE_41__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_51__ {int /*<<< orphan*/  len; } ;
struct TYPE_42__ {TYPE_3__ key; int /*<<< orphan*/  lowcase_key; int /*<<< orphan*/  hash; } ;
typedef  TYPE_11__ ngx_table_elt_t ;
struct TYPE_43__ {char* data; } ;
typedef  TYPE_12__ ngx_str_t ;
struct TYPE_44__ {size_t nelts; TYPE_11__* elts; struct TYPE_44__* next; } ;
typedef  TYPE_13__ ngx_list_part_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_50__ {TYPE_13__ part; } ;
struct TYPE_57__ {int /*<<< orphan*/  content_length_n; int /*<<< orphan*/  status_line; int /*<<< orphan*/  status_n; TYPE_2__ headers; TYPE_1__* x_accel_redirect; } ;
struct TYPE_45__ {int length; TYPE_10__* conf; int /*<<< orphan*/  cacheable; TYPE_9__ headers_in; } ;
typedef  TYPE_14__ ngx_http_upstream_t ;
struct TYPE_46__ {int /*<<< orphan*/  headers_in_hash; } ;
typedef  TYPE_15__ ngx_http_upstream_main_conf_t ;
struct TYPE_47__ {scalar_t__ (* copy_handler ) (TYPE_17__*,TYPE_11__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  conf; scalar_t__ redirect; } ;
typedef  TYPE_16__ ngx_http_upstream_header_t ;
struct TYPE_56__ {int /*<<< orphan*/  content_length_n; int /*<<< orphan*/  status_line; int /*<<< orphan*/  status; TYPE_7__* date; TYPE_5__* server; } ;
struct TYPE_48__ {scalar_t__ method; int disable_not_modified; int allow_ranges; int single_range; scalar_t__ cached; TYPE_8__ headers_out; int /*<<< orphan*/  method_name; } ;
typedef  TYPE_17__ ngx_http_request_t ;
struct TYPE_54__ {int /*<<< orphan*/ * data; } ;
struct TYPE_55__ {scalar_t__ hash; TYPE_6__ value; } ;
struct TYPE_52__ {int /*<<< orphan*/ * data; } ;
struct TYPE_53__ {scalar_t__ hash; TYPE_4__ value; } ;
struct TYPE_49__ {TYPE_12__ value; } ;
struct TYPE_41__ {int ignore_headers; scalar_t__ force_ranges; int /*<<< orphan*/  hide_headers_hash; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_HTTP_GET ; 
 scalar_t__ NGX_HTTP_HEAD ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 size_t NGX_HTTP_LOG_UNSAFE ; 
 scalar_t__ NGX_HTTP_NOT_FOUND ; 
 int NGX_HTTP_UPSTREAM_IGN_XA_REDIRECT ; 
 scalar_t__ NGX_OK ; 
 TYPE_16__* ngx_hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_get_method ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_17__*,scalar_t__) ; 
 TYPE_15__* ngx_http_get_module_main_conf (TYPE_17__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_internal_redirect (TYPE_17__*,TYPE_12__*,TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_http_named_location (TYPE_17__*,TYPE_12__*) ; 
 scalar_t__ ngx_http_parse_unsafe_uri (TYPE_17__*,TYPE_12__*,TYPE_12__*,size_t*) ; 
 scalar_t__ ngx_http_upstream_copy_header_line (TYPE_17__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_17__*,TYPE_14__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_upstream_module ; 
 int /*<<< orphan*/  ngx_str_null (TYPE_12__*) ; 
 scalar_t__ stub1 (TYPE_17__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_17__*,TYPE_11__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_headers(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    ngx_str_t                       uri, args;
    ngx_uint_t                      i, flags;
    ngx_list_part_t                *part;
    ngx_table_elt_t                *h;
    ngx_http_upstream_header_t     *hh;
    ngx_http_upstream_main_conf_t  *umcf;

    umcf = ngx_http_get_module_main_conf(r, ngx_http_upstream_module);

    if (u->headers_in.x_accel_redirect
        && !(u->conf->ignore_headers & NGX_HTTP_UPSTREAM_IGN_XA_REDIRECT))
    {
        ngx_http_upstream_finalize_request(r, u, NGX_DECLINED);

        part = &u->headers_in.headers.part;
        h = part->elts;

        for (i = 0; /* void */; i++) {

            if (i >= part->nelts) {
                if (part->next == NULL) {
                    break;
                }

                part = part->next;
                h = part->elts;
                i = 0;
            }

            hh = ngx_hash_find(&umcf->headers_in_hash, h[i].hash,
                               h[i].lowcase_key, h[i].key.len);

            if (hh && hh->redirect) {
                if (hh->copy_handler(r, &h[i], hh->conf) != NGX_OK) {
                    ngx_http_finalize_request(r,
                                              NGX_HTTP_INTERNAL_SERVER_ERROR);
                    return NGX_DONE;
                }
            }
        }

        uri = u->headers_in.x_accel_redirect->value;

        if (uri.data[0] == '@') {
            ngx_http_named_location(r, &uri);

        } else {
            ngx_str_null(&args);
            flags = NGX_HTTP_LOG_UNSAFE;

            if (ngx_http_parse_unsafe_uri(r, &uri, &args, &flags) != NGX_OK) {
                ngx_http_finalize_request(r, NGX_HTTP_NOT_FOUND);
                return NGX_DONE;
            }

            if (r->method != NGX_HTTP_HEAD) {
                r->method = NGX_HTTP_GET;
                r->method_name = ngx_http_core_get_method;
            }

            ngx_http_internal_redirect(r, &uri, &args);
        }

        ngx_http_finalize_request(r, NGX_DONE);
        return NGX_DONE;
    }

    part = &u->headers_in.headers.part;
    h = part->elts;

    for (i = 0; /* void */; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            h = part->elts;
            i = 0;
        }

        if (ngx_hash_find(&u->conf->hide_headers_hash, h[i].hash,
                          h[i].lowcase_key, h[i].key.len))
        {
            continue;
        }

        hh = ngx_hash_find(&umcf->headers_in_hash, h[i].hash,
                           h[i].lowcase_key, h[i].key.len);

        if (hh) {
            if (hh->copy_handler(r, &h[i], hh->conf) != NGX_OK) {
                ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
                return NGX_DONE;
            }

            continue;
        }

        if (ngx_http_upstream_copy_header_line(r, &h[i], 0) != NGX_OK) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return NGX_DONE;
        }
    }

    if (r->headers_out.server && r->headers_out.server->value.data == NULL) {
        r->headers_out.server->hash = 0;
    }

    if (r->headers_out.date && r->headers_out.date->value.data == NULL) {
        r->headers_out.date->hash = 0;
    }

    r->headers_out.status = u->headers_in.status_n;
    r->headers_out.status_line = u->headers_in.status_line;

    r->headers_out.content_length_n = u->headers_in.content_length_n;

    r->disable_not_modified = !u->cacheable;

    if (u->conf->force_ranges) {
        r->allow_ranges = 1;
        r->single_range = 1;

#if (NGX_HTTP_CACHE)
        if (r->cached) {
            r->single_range = 0;
        }
#endif
    }

    u->length = -1;

    return NGX_OK;
}