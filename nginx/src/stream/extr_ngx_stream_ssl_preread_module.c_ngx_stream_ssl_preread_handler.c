#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_16__ {int /*<<< orphan*/  enabled; } ;
typedef  TYPE_2__ ngx_stream_ssl_preread_srv_conf_t ;
struct TYPE_17__ {int* pos; int* version; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_stream_ssl_preread_ctx_t ;
struct TYPE_18__ {TYPE_5__* connection; } ;
typedef  TYPE_4__ ngx_stream_session_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_19__ {scalar_t__ type; TYPE_1__* buffer; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_15__ {int* pos; int* last; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ngx_stream_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_stream_get_module_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_set_ctx (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_ssl_preread_module ; 
 scalar_t__ ngx_stream_ssl_preread_parse_record (TYPE_3__*,int*,int*) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_ssl_preread_handler(ngx_stream_session_t *s)
{
    u_char                             *last, *p;
    size_t                              len;
    ngx_int_t                           rc;
    ngx_connection_t                   *c;
    ngx_stream_ssl_preread_ctx_t       *ctx;
    ngx_stream_ssl_preread_srv_conf_t  *sscf;

    c = s->connection;

    ngx_log_debug0(NGX_LOG_DEBUG_STREAM, c->log, 0, "ssl preread handler");

    sscf = ngx_stream_get_module_srv_conf(s, ngx_stream_ssl_preread_module);

    if (!sscf->enabled) {
        return NGX_DECLINED;
    }

    if (c->type != SOCK_STREAM) {
        return NGX_DECLINED;
    }

    if (c->buffer == NULL) {
        return NGX_AGAIN;
    }

    ctx = ngx_stream_get_module_ctx(s, ngx_stream_ssl_preread_module);
    if (ctx == NULL) {
        ctx = ngx_pcalloc(c->pool, sizeof(ngx_stream_ssl_preread_ctx_t));
        if (ctx == NULL) {
            return NGX_ERROR;
        }

        ngx_stream_set_ctx(s, ctx, ngx_stream_ssl_preread_module);

        ctx->pool = c->pool;
        ctx->log = c->log;
        ctx->pos = c->buffer->pos;
    }

    p = ctx->pos;
    last = c->buffer->last;

    while (last - p >= 5) {

        if ((p[0] & 0x80) && p[2] == 1 && (p[3] == 0 || p[3] == 3)) {
            ngx_log_debug0(NGX_LOG_DEBUG_STREAM, ctx->log, 0,
                           "ssl preread: version 2 ClientHello");
            ctx->version[0] = p[3];
            ctx->version[1] = p[4];
            return NGX_OK;
        }

        if (p[0] != 0x16) {
            ngx_log_debug0(NGX_LOG_DEBUG_STREAM, ctx->log, 0,
                           "ssl preread: not a handshake");
            ngx_stream_set_ctx(s, NULL, ngx_stream_ssl_preread_module);
            return NGX_DECLINED;
        }

        if (p[1] != 3) {
            ngx_log_debug0(NGX_LOG_DEBUG_STREAM, ctx->log, 0,
                           "ssl preread: unsupported SSL version");
            ngx_stream_set_ctx(s, NULL, ngx_stream_ssl_preread_module);
            return NGX_DECLINED;
        }

        len = (p[3] << 8) + p[4];

        /* read the whole record before parsing */
        if ((size_t) (last - p) < len + 5) {
            break;
        }

        p += 5;

        rc = ngx_stream_ssl_preread_parse_record(ctx, p, p + len);

        if (rc == NGX_DECLINED) {
            ngx_stream_set_ctx(s, NULL, ngx_stream_ssl_preread_module);
            return NGX_DECLINED;
        }

        if (rc != NGX_AGAIN) {
            return rc;
        }

        p += len;
    }

    ctx->pos = p;

    return NGX_AGAIN;
}