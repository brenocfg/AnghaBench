#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_34__ {scalar_t__ len; char* data; } ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_35__ {TYPE_4__* connection; } ;
typedef  TYPE_6__ ngx_rtmp_session_t ;
struct TYPE_36__ {char* name; int /*<<< orphan*/  args; scalar_t__ start; } ;
typedef  TYPE_7__ ngx_rtmp_play_t ;
struct TYPE_31__ {scalar_t__ nelts; TYPE_9__** elts; } ;
struct TYPE_37__ {TYPE_2__ fmts; } ;
typedef  TYPE_8__ ngx_rtmp_play_main_conf_t ;
struct TYPE_38__ {int /*<<< orphan*/  name; TYPE_5__ sfx; TYPE_5__ pfx; } ;
typedef  TYPE_9__ ngx_rtmp_play_fmt_t ;
struct TYPE_32__ {scalar_t__ fd; int /*<<< orphan*/  log; } ;
struct TYPE_28__ {scalar_t__ pfx_size; TYPE_9__* fmt; TYPE_5__ sfx; void* post_seek; void* nentry; TYPE_3__ file; int /*<<< orphan*/  name; void* vindex; void* aindex; TYPE_6__* session; } ;
typedef  TYPE_10__ ngx_rtmp_play_ctx_t ;
struct TYPE_30__ {scalar_t__ nelts; } ;
struct TYPE_29__ {TYPE_1__ entries; } ;
typedef  TYPE_11__ ngx_rtmp_play_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_33__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 void* NGX_CONF_UNSET_UINT ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_RTMP_MAX_NAME ; 
 int /*<<< orphan*/  next_play (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_10__*,int) ; 
 TYPE_10__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_path_separator (char) ; 
 TYPE_11__* ngx_rtmp_get_module_app_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* ngx_rtmp_get_module_ctx (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_rtmp_get_module_main_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 
 int /*<<< orphan*/  ngx_rtmp_play_next_entry (TYPE_6__*,TYPE_7__*) ; 
 void* ngx_rtmp_play_parse_index (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_6__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strlen (char*) ; 
 scalar_t__ ngx_strncasecmp (char*,char*,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_play_play(ngx_rtmp_session_t *s, ngx_rtmp_play_t *v)
{
    ngx_rtmp_play_main_conf_t      *pmcf;
    ngx_rtmp_play_app_conf_t       *pacf;
    ngx_rtmp_play_ctx_t            *ctx;
    u_char                         *p;
    ngx_rtmp_play_fmt_t            *fmt, **pfmt;
    ngx_str_t                      *pfx, *sfx;
    ngx_str_t                       name;
    ngx_uint_t                      n;

    pmcf = ngx_rtmp_get_module_main_conf(s, ngx_rtmp_play_module);

    pacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_play_module);

    if (pacf == NULL || pacf->entries.nelts == 0) {
        goto next;
    }

    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
                  "play: play name='%s' timestamp=%i",
                  v->name, (ngx_int_t) v->start);

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_play_module);

    if (ctx && ctx->file.fd != NGX_INVALID_FILE) {
        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                     "play: already playing");
        goto next;
    }

    /* check for double-dot in v->name;
     * we should not move out of play directory */
    for (p = v->name; *p; ++p) {
        if (ngx_path_separator(p[0]) &&
            p[1] == '.' && p[2] == '.' &&
            ngx_path_separator(p[3]))
        {
            ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                         "play: bad name '%s'", v->name);
            return NGX_ERROR;
        }
    }

    if (ctx == NULL) {
        ctx = ngx_palloc(s->connection->pool, sizeof(ngx_rtmp_play_ctx_t));
        ngx_rtmp_set_ctx(s, ctx, ngx_rtmp_play_module);
    }

    ngx_memzero(ctx, sizeof(*ctx));

    ctx->session = s;
    ctx->aindex = ngx_rtmp_play_parse_index('a', v->args);
    ctx->vindex = ngx_rtmp_play_parse_index('v', v->args);

    ctx->file.log = s->connection->log;

    ngx_memcpy(ctx->name, v->name, NGX_RTMP_MAX_NAME);

    name.len = ngx_strlen(v->name);
    name.data = v->name;

    pfmt = pmcf->fmts.elts;

    for (n = 0; n < pmcf->fmts.nelts; ++n, ++pfmt) {
        fmt = *pfmt;

        pfx = &fmt->pfx;
        sfx = &fmt->sfx;

        if (pfx->len == 0 && ctx->fmt == NULL) {
            ctx->fmt = fmt;
        }

        if (pfx->len && name.len >= pfx->len &&
            ngx_strncasecmp(pfx->data, name.data, pfx->len) == 0)
        {
            ctx->pfx_size = pfx->len;
            ctx->fmt = fmt;

            break;
        }

        if (name.len >= sfx->len &&
            ngx_strncasecmp(sfx->data, name.data + name.len - sfx->len,
                            sfx->len) == 0)
        {
            ctx->fmt = fmt;
        }
    }

    if (ctx->fmt == NULL) {
        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                      "play: fmt not found");
        goto next;
    }

    ctx->file.fd = NGX_INVALID_FILE;
    ctx->nentry = NGX_CONF_UNSET_UINT;
    ctx->post_seek = NGX_CONF_UNSET_UINT;

    sfx = &ctx->fmt->sfx;

    if (name.len < sfx->len ||
        ngx_strncasecmp(sfx->data, name.data + name.len - sfx->len,
                        sfx->len))
    {
        ctx->sfx = *sfx;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "play: fmt=%V", &ctx->fmt->name);

    return ngx_rtmp_play_next_entry(s, v);

next:
    return next_play(s, v);
}