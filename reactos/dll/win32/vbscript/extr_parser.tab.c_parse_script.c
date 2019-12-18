#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* code; char const* ptr; char const* end; void* parse_complete; int /*<<< orphan*/  hres; int /*<<< orphan*/  is_html; void* option_explicit; int /*<<< orphan*/ * class_decls; int /*<<< orphan*/ * stats_tail; int /*<<< orphan*/  stats; scalar_t__ last_nl; int /*<<< orphan*/  last_token; int /*<<< orphan*/  heap; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  heap_pool_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser_parse (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmpiW (char const*,char const*) ; 
 int strlenW (char const*) ; 
 int /*<<< orphan*/  tNL ; 

HRESULT parse_script(parser_ctx_t *ctx, const WCHAR *code, const WCHAR *delimiter)
{
    static const WCHAR html_delimiterW[] = {'<','/','s','c','r','i','p','t','>',0};

    ctx->code = ctx->ptr = code;
    ctx->end = ctx->code + strlenW(ctx->code);

    heap_pool_init(&ctx->heap);

    ctx->parse_complete = FALSE;
    ctx->hres = S_OK;

    ctx->last_token = tNL;
    ctx->last_nl = 0;
    ctx->stats = ctx->stats_tail = NULL;
    ctx->class_decls = NULL;
    ctx->option_explicit = FALSE;
    ctx->is_html = delimiter && !strcmpiW(delimiter, html_delimiterW);

    parser_parse(ctx);

    if(FAILED(ctx->hres))
        return ctx->hres;
    if(!ctx->parse_complete) {
        FIXME("parser failed around %s\n", debugstr_w(ctx->code+20 > ctx->ptr ? ctx->code : ctx->ptr-20));
        return E_FAIL;
    }

    return S_OK;
}