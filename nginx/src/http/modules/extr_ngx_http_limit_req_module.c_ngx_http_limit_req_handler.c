#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_23__ ;
typedef  struct TYPE_28__   TYPE_21__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_36__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_8__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_37__ {TYPE_7__* connection; int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  read_event_handler; TYPE_6__* main; } ;
typedef  TYPE_9__ ngx_http_request_t ;
struct TYPE_24__ {TYPE_5__* shm_zone; } ;
typedef  TYPE_10__ ngx_http_limit_req_limit_t ;
struct TYPE_28__ {int /*<<< orphan*/  value; } ;
struct TYPE_25__ {TYPE_3__* node; TYPE_2__* shpool; TYPE_21__ key; } ;
typedef  TYPE_11__ ngx_http_limit_req_ctx_t ;
struct TYPE_27__ {size_t nelts; TYPE_10__* elts; } ;
struct TYPE_26__ {scalar_t__ status_code; scalar_t__ dry_run; int /*<<< orphan*/  delay_log_level; int /*<<< orphan*/  limit_log_level; TYPE_1__ limits; } ;
typedef  TYPE_12__ ngx_http_limit_req_conf_t ;
struct TYPE_35__ {TYPE_23__* write; int /*<<< orphan*/  read; int /*<<< orphan*/  log; } ;
struct TYPE_34__ {scalar_t__ limit_req_status; } ;
struct TYPE_32__ {int /*<<< orphan*/  name; } ;
struct TYPE_33__ {TYPE_4__ shm; TYPE_11__* data; } ;
struct TYPE_31__ {int /*<<< orphan*/  count; } ;
struct TYPE_30__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_29__ {int delayed; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_LIMIT_REQ_DELAYED ; 
 scalar_t__ NGX_HTTP_LIMIT_REQ_DELAYED_DRY_RUN ; 
 scalar_t__ NGX_HTTP_LIMIT_REQ_PASSED ; 
 scalar_t__ NGX_HTTP_LIMIT_REQ_REJECTED ; 
 scalar_t__ NGX_HTTP_LIMIT_REQ_REJECTED_DRY_RUN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_23__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_crc32_short (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_handle_read_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_complex_value (TYPE_9__*,TYPE_21__*,TYPE_8__*) ; 
 TYPE_12__* ngx_http_get_module_loc_conf (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_limit_req_account (TYPE_10__*,size_t,size_t*,TYPE_10__**) ; 
 int /*<<< orphan*/  ngx_http_limit_req_delay ; 
 scalar_t__ ngx_http_limit_req_lookup (TYPE_10__*,int /*<<< orphan*/ ,TYPE_8__*,size_t*,int) ; 
 int /*<<< orphan*/  ngx_http_limit_req_module ; 
 int /*<<< orphan*/  ngx_http_test_reading ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,scalar_t__,size_t,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_limit_req_handler(ngx_http_request_t *r)
{
    uint32_t                     hash;
    ngx_str_t                    key;
    ngx_int_t                    rc;
    ngx_uint_t                   n, excess;
    ngx_msec_t                   delay;
    ngx_http_limit_req_ctx_t    *ctx;
    ngx_http_limit_req_conf_t   *lrcf;
    ngx_http_limit_req_limit_t  *limit, *limits;

    if (r->main->limit_req_status) {
        return NGX_DECLINED;
    }

    lrcf = ngx_http_get_module_loc_conf(r, ngx_http_limit_req_module);
    limits = lrcf->limits.elts;

    excess = 0;

    rc = NGX_DECLINED;

#if (NGX_SUPPRESS_WARN)
    limit = NULL;
#endif

    for (n = 0; n < lrcf->limits.nelts; n++) {

        limit = &limits[n];

        ctx = limit->shm_zone->data;

        if (ngx_http_complex_value(r, &ctx->key, &key) != NGX_OK) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        if (key.len == 0) {
            continue;
        }

        if (key.len > 65535) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "the value of the \"%V\" key "
                          "is more than 65535 bytes: \"%V\"",
                          &ctx->key.value, &key);
            continue;
        }

        hash = ngx_crc32_short(key.data, key.len);

        ngx_shmtx_lock(&ctx->shpool->mutex);

        rc = ngx_http_limit_req_lookup(limit, hash, &key, &excess,
                                       (n == lrcf->limits.nelts - 1));

        ngx_shmtx_unlock(&ctx->shpool->mutex);

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "limit_req[%ui]: %i %ui.%03ui",
                       n, rc, excess / 1000, excess % 1000);

        if (rc != NGX_AGAIN) {
            break;
        }
    }

    if (rc == NGX_DECLINED) {
        return NGX_DECLINED;
    }

    if (rc == NGX_BUSY || rc == NGX_ERROR) {

        if (rc == NGX_BUSY) {
            ngx_log_error(lrcf->limit_log_level, r->connection->log, 0,
                        "limiting requests%s, excess: %ui.%03ui by zone \"%V\"",
                        lrcf->dry_run ? ", dry run" : "",
                        excess / 1000, excess % 1000,
                        &limit->shm_zone->shm.name);
        }

        while (n--) {
            ctx = limits[n].shm_zone->data;

            if (ctx->node == NULL) {
                continue;
            }

            ngx_shmtx_lock(&ctx->shpool->mutex);

            ctx->node->count--;

            ngx_shmtx_unlock(&ctx->shpool->mutex);

            ctx->node = NULL;
        }

        if (lrcf->dry_run) {
            r->main->limit_req_status = NGX_HTTP_LIMIT_REQ_REJECTED_DRY_RUN;
            return NGX_DECLINED;
        }

        r->main->limit_req_status = NGX_HTTP_LIMIT_REQ_REJECTED;

        return lrcf->status_code;
    }

    /* rc == NGX_AGAIN || rc == NGX_OK */

    if (rc == NGX_AGAIN) {
        excess = 0;
    }

    delay = ngx_http_limit_req_account(limits, n, &excess, &limit);

    if (!delay) {
        r->main->limit_req_status = NGX_HTTP_LIMIT_REQ_PASSED;
        return NGX_DECLINED;
    }

    ngx_log_error(lrcf->delay_log_level, r->connection->log, 0,
                  "delaying request%s, excess: %ui.%03ui, by zone \"%V\"",
                  lrcf->dry_run ? ", dry run" : "",
                  excess / 1000, excess % 1000, &limit->shm_zone->shm.name);

    if (lrcf->dry_run) {
        r->main->limit_req_status = NGX_HTTP_LIMIT_REQ_DELAYED_DRY_RUN;
        return NGX_DECLINED;
    }

    r->main->limit_req_status = NGX_HTTP_LIMIT_REQ_DELAYED;

    if (ngx_handle_read_event(r->connection->read, 0) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    r->read_event_handler = ngx_http_test_reading;
    r->write_event_handler = ngx_http_limit_req_delay;

    r->connection->write->delayed = 1;
    ngx_add_timer(r->connection->write, delay);

    return NGX_AGAIN;
}