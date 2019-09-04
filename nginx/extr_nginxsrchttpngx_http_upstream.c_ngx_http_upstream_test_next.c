#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
typedef  scalar_t__ ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {int tries; scalar_t__ start_time; } ;
struct TYPE_12__ {scalar_t__ status_n; } ;
struct TYPE_15__ {TYPE_3__ peer; scalar_t__ request_sent; TYPE_2__* conf; TYPE_1__ headers_in; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_16__ {scalar_t__ status; scalar_t__ mask; } ;
typedef  TYPE_5__ ngx_http_upstream_next_t ;
struct TYPE_17__ {int method; scalar_t__ request_body_no_buffering; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_13__ {scalar_t__ next_upstream_timeout; scalar_t__ next_upstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int NGX_HTTP_LOCK ; 
 int NGX_HTTP_PATCH ; 
 int NGX_HTTP_POST ; 
 scalar_t__ NGX_HTTP_UPSTREAM_FT_NON_IDEMPOTENT ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_current_msec ; 
 int /*<<< orphan*/  ngx_http_upstream_next (TYPE_6__*,TYPE_4__*,scalar_t__) ; 
 TYPE_5__* ngx_http_upstream_next_errors ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_test_next(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    ngx_msec_t                 timeout;
    ngx_uint_t                 status, mask;
    ngx_http_upstream_next_t  *un;

    status = u->headers_in.status_n;

    for (un = ngx_http_upstream_next_errors; un->status; un++) {

        if (status != un->status) {
            continue;
        }

        timeout = u->conf->next_upstream_timeout;

        if (u->request_sent
            && (r->method & (NGX_HTTP_POST|NGX_HTTP_LOCK|NGX_HTTP_PATCH)))
        {
            mask = un->mask | NGX_HTTP_UPSTREAM_FT_NON_IDEMPOTENT;

        } else {
            mask = un->mask;
        }

        if (u->peer.tries > 1
            && ((u->conf->next_upstream & mask) == mask)
            && !(u->request_sent && r->request_body_no_buffering)
            && !(timeout && ngx_current_msec - u->peer.start_time >= timeout))
        {
            ngx_http_upstream_next(r, u, un->mask);
            return NGX_OK;
        }

#if (NGX_HTTP_CACHE)

        if (u->cache_status == NGX_HTTP_CACHE_EXPIRED
            && ((u->conf->cache_use_stale & un->mask) || r->cache->stale_error))
        {
            ngx_int_t  rc;

            rc = u->reinit_request(r);

            if (rc != NGX_OK) {
                ngx_http_upstream_finalize_request(r, u, rc);
                return NGX_OK;
            }

            u->cache_status = NGX_HTTP_CACHE_STALE;
            rc = ngx_http_upstream_cache_send(r, u);

            if (rc == NGX_DONE) {
                return NGX_OK;
            }

            if (rc == NGX_HTTP_UPSTREAM_INVALID_HEADER) {
                rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
            }

            ngx_http_upstream_finalize_request(r, u, rc);
            return NGX_OK;
        }

#endif
    }

#if (NGX_HTTP_CACHE)

    if (status == NGX_HTTP_NOT_MODIFIED
        && u->cache_status == NGX_HTTP_CACHE_EXPIRED
        && u->conf->cache_revalidate)
    {
        time_t     now, valid, updating, error;
        ngx_int_t  rc;

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http upstream not modified");

        now = ngx_time();

        valid = r->cache->valid_sec;
        updating = r->cache->updating_sec;
        error = r->cache->error_sec;

        rc = u->reinit_request(r);

        if (rc != NGX_OK) {
            ngx_http_upstream_finalize_request(r, u, rc);
            return NGX_OK;
        }

        u->cache_status = NGX_HTTP_CACHE_REVALIDATED;
        rc = ngx_http_upstream_cache_send(r, u);

        if (rc == NGX_DONE) {
            return NGX_OK;
        }

        if (rc == NGX_HTTP_UPSTREAM_INVALID_HEADER) {
            rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        if (valid == 0) {
            valid = r->cache->valid_sec;
            updating = r->cache->updating_sec;
            error = r->cache->error_sec;
        }

        if (valid == 0) {
            valid = ngx_http_file_cache_valid(u->conf->cache_valid,
                                              u->headers_in.status_n);
            if (valid) {
                valid = now + valid;
            }
        }

        if (valid) {
            r->cache->valid_sec = valid;
            r->cache->updating_sec = updating;
            r->cache->error_sec = error;

            r->cache->date = now;

            ngx_http_file_cache_update_header(r);
        }

        ngx_http_upstream_finalize_request(r, u, rc);
        return NGX_OK;
    }

#endif

    return NGX_DECLINED;
}