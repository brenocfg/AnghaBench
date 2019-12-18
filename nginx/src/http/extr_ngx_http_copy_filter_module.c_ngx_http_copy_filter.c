#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_output_chain_filter_pt ;
struct TYPE_17__ {int need_in_memory; int /*<<< orphan*/ * in; int /*<<< orphan*/  aio; int /*<<< orphan*/  thread_handler; int /*<<< orphan*/  aio_preload; int /*<<< orphan*/  aio_handler; TYPE_2__* filter_ctx; scalar_t__ output_filter; scalar_t__ tag; int /*<<< orphan*/  bufs; int /*<<< orphan*/  pool; int /*<<< orphan*/  alignment; int /*<<< orphan*/  need_in_temp; int /*<<< orphan*/  sendfile; } ;
typedef  TYPE_1__ ngx_output_chain_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_18__ {int request_output; int /*<<< orphan*/  args; int /*<<< orphan*/  uri; int /*<<< orphan*/  buffered; int /*<<< orphan*/  aio; int /*<<< orphan*/  pool; int /*<<< orphan*/  filter_need_temporary; scalar_t__ filter_need_in_memory; scalar_t__ main_filter_need_in_memory; TYPE_5__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_19__ {scalar_t__ aio; int /*<<< orphan*/  directio_alignment; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
struct TYPE_20__ {int /*<<< orphan*/  bufs; } ;
typedef  TYPE_4__ ngx_http_copy_filter_conf_t ;
struct TYPE_21__ {int /*<<< orphan*/  log; int /*<<< orphan*/  sendfile; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_22__ {scalar_t__ buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
typedef  scalar_t__ ngx_buf_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_AIO_ON ; 
 scalar_t__ NGX_HTTP_AIO_THREADS ; 
 int /*<<< orphan*/  NGX_HTTP_COPY_BUFFERED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ ngx_buf_size (scalar_t__) ; 
 scalar_t__ ngx_file_aio ; 
 int /*<<< orphan*/  ngx_http_copy_aio_handler ; 
 int /*<<< orphan*/  ngx_http_copy_aio_sendfile_preload ; 
 int /*<<< orphan*/  ngx_http_copy_filter_module ; 
 int /*<<< orphan*/  ngx_http_copy_thread_handler ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_1__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_next_body_filter ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_output_chain (TYPE_1__*,TYPE_6__*) ; 
 TYPE_1__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_copy_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_int_t                     rc;
    ngx_connection_t             *c;
    ngx_output_chain_ctx_t       *ctx;
    ngx_http_core_loc_conf_t     *clcf;
    ngx_http_copy_filter_conf_t  *conf;

    c = r->connection;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http copy filter: \"%V?%V\"", &r->uri, &r->args);

    ctx = ngx_http_get_module_ctx(r, ngx_http_copy_filter_module);

    if (ctx == NULL) {
        ctx = ngx_pcalloc(r->pool, sizeof(ngx_output_chain_ctx_t));
        if (ctx == NULL) {
            return NGX_ERROR;
        }

        ngx_http_set_ctx(r, ctx, ngx_http_copy_filter_module);

        conf = ngx_http_get_module_loc_conf(r, ngx_http_copy_filter_module);
        clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

        ctx->sendfile = c->sendfile;
        ctx->need_in_memory = r->main_filter_need_in_memory
                              || r->filter_need_in_memory;
        ctx->need_in_temp = r->filter_need_temporary;

        ctx->alignment = clcf->directio_alignment;

        ctx->pool = r->pool;
        ctx->bufs = conf->bufs;
        ctx->tag = (ngx_buf_tag_t) &ngx_http_copy_filter_module;

        ctx->output_filter = (ngx_output_chain_filter_pt)
                                  ngx_http_next_body_filter;
        ctx->filter_ctx = r;

#if (NGX_HAVE_FILE_AIO)
        if (ngx_file_aio && clcf->aio == NGX_HTTP_AIO_ON) {
            ctx->aio_handler = ngx_http_copy_aio_handler;
#if (NGX_HAVE_AIO_SENDFILE)
            ctx->aio_preload = ngx_http_copy_aio_sendfile_preload;
#endif
        }
#endif

#if (NGX_THREADS)
        if (clcf->aio == NGX_HTTP_AIO_THREADS) {
            ctx->thread_handler = ngx_http_copy_thread_handler;
        }
#endif

        if (in && in->buf && ngx_buf_size(in->buf)) {
            r->request_output = 1;
        }
    }

#if (NGX_HAVE_FILE_AIO || NGX_THREADS)
    ctx->aio = r->aio;
#endif

    rc = ngx_output_chain(ctx, in);

    if (ctx->in == NULL) {
        r->buffered &= ~NGX_HTTP_COPY_BUFFERED;

    } else {
        r->buffered |= NGX_HTTP_COPY_BUFFERED;
    }

    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http copy filter: %i \"%V?%V\"", rc, &r->uri, &r->args);

    return rc;
}