#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {TYPE_3__* ctxt; TYPE_5__* request; } ;
typedef  TYPE_4__ ngx_http_xslt_filter_ctx_t ;
struct TYPE_17__ {TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_18__ {scalar_t__ last; scalar_t__ pos; scalar_t__ last_in_chain; scalar_t__ last_buf; } ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_15__ {TYPE_1__* sax; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;
struct TYPE_13__ {TYPE_4__* _private; void* fatalError; void* error; int /*<<< orphan*/ * setDocumentLocator; int /*<<< orphan*/  externalSubset; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int XML_PARSE_DTDLOAD ; 
 int XML_PARSE_NOENT ; 
 int XML_PARSE_NOWARNING ; 
 void* ngx_http_xslt_sax_error ; 
 int /*<<< orphan*/  ngx_http_xslt_sax_external_subset ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* xmlCreatePushParserCtxt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlCtxtUseOptions (TYPE_3__*,int) ; 
 int xmlParseChunk (TYPE_3__*,char*,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_xslt_add_chunk(ngx_http_request_t *r, ngx_http_xslt_filter_ctx_t *ctx,
    ngx_buf_t *b)
{
    int               err;
    xmlParserCtxtPtr  ctxt;

    if (ctx->ctxt == NULL) {

        ctxt = xmlCreatePushParserCtxt(NULL, NULL, NULL, 0, NULL);
        if (ctxt == NULL) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "xmlCreatePushParserCtxt() failed");
            return NGX_ERROR;
        }
        xmlCtxtUseOptions(ctxt, XML_PARSE_NOENT|XML_PARSE_DTDLOAD
                                               |XML_PARSE_NOWARNING);

        ctxt->sax->externalSubset = ngx_http_xslt_sax_external_subset;
        ctxt->sax->setDocumentLocator = NULL;
        ctxt->sax->error = ngx_http_xslt_sax_error;
        ctxt->sax->fatalError = ngx_http_xslt_sax_error;
        ctxt->sax->_private = ctx;

        ctx->ctxt = ctxt;
        ctx->request = r;
    }

    err = xmlParseChunk(ctx->ctxt, (char *) b->pos, (int) (b->last - b->pos),
                        (b->last_buf) || (b->last_in_chain));

    if (err == 0) {
        b->pos = b->last;
        return NGX_OK;
    }

    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                  "xmlParseChunk() failed, error:%d", err);

    return NGX_ERROR;
}