#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_22__ {TYPE_6__* doc; TYPE_5__* ctxt; scalar_t__ done; } ;
typedef  TYPE_2__ ngx_http_xslt_filter_ctx_t ;
struct TYPE_23__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_24__ {TYPE_15__* buf; struct TYPE_24__* next; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_26__ {int /*<<< orphan*/ * extSubset; } ;
struct TYPE_25__ {int wellFormed; TYPE_6__* myDoc; } ;
struct TYPE_21__ {int /*<<< orphan*/  log; } ;
struct TYPE_20__ {scalar_t__ last_in_chain; scalar_t__ last_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_2__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_next_body_filter (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ ngx_http_xslt_add_chunk (TYPE_3__*,TYPE_2__*,TYPE_15__*) ; 
 int /*<<< orphan*/ * ngx_http_xslt_apply_stylesheet (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_xslt_filter_module ; 
 scalar_t__ ngx_http_xslt_send (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFreeDoc (TYPE_6__*) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (TYPE_5__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_xslt_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    int                          wellFormed;
    ngx_chain_t                 *cl;
    ngx_http_xslt_filter_ctx_t  *ctx;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "xslt filter body");

    if (in == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_xslt_filter_module);

    if (ctx == NULL || ctx->done) {
        return ngx_http_next_body_filter(r, in);
    }

    for (cl = in; cl; cl = cl->next) {

        if (ngx_http_xslt_add_chunk(r, ctx, cl->buf) != NGX_OK) {

            if (ctx->ctxt->myDoc) {

#if (NGX_HTTP_XSLT_REUSE_DTD)
                ctx->ctxt->myDoc->extSubset = NULL;
#endif
                xmlFreeDoc(ctx->ctxt->myDoc);
            }

            xmlFreeParserCtxt(ctx->ctxt);

            return ngx_http_xslt_send(r, ctx, NULL);
        }

        if (cl->buf->last_buf || cl->buf->last_in_chain) {

            ctx->doc = ctx->ctxt->myDoc;

#if (NGX_HTTP_XSLT_REUSE_DTD)
            ctx->doc->extSubset = NULL;
#endif

            wellFormed = ctx->ctxt->wellFormed;

            xmlFreeParserCtxt(ctx->ctxt);

            if (wellFormed) {
                return ngx_http_xslt_send(r, ctx,
                                       ngx_http_xslt_apply_stylesheet(r, ctx));
            }

            xmlFreeDoc(ctx->doc);

            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "not well formed XML document");

            return ngx_http_xslt_send(r, ctx, NULL);
        }
    }

    return NGX_OK;
}