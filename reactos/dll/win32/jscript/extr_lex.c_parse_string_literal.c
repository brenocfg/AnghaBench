#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* ptr; scalar_t__* end; int /*<<< orphan*/  compiler; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  JS_E_UNTERMINATED_STRING ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/ * compiler_alloc_string_len (int /*<<< orphan*/ ,scalar_t__ const*,size_t) ; 
 int lex_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,size_t) ; 
 scalar_t__* parser_alloc (TYPE_1__*,size_t) ; 
 int tStringLiteral ; 
 int /*<<< orphan*/  unescape (scalar_t__*,size_t*) ; 

__attribute__((used)) static int parse_string_literal(parser_ctx_t *ctx, jsstr_t **ret, WCHAR endch)
{
    const WCHAR *ptr = ++ctx->ptr, *ret_str = ptr;
    BOOL needs_unescape = FALSE;
    WCHAR *unescape_str;
    size_t len;

    while(ctx->ptr < ctx->end && *ctx->ptr != endch) {
        if(*ctx->ptr++ == '\\') {
            ctx->ptr++;
            needs_unescape = TRUE;
        }
    }

    if(ctx->ptr == ctx->end)
        return lex_error(ctx, JS_E_UNTERMINATED_STRING);

    len = ctx->ptr - ptr;
    ctx->ptr++;

    if(needs_unescape) {
        ret_str = unescape_str = parser_alloc(ctx, len * sizeof(WCHAR));
        if(!unescape_str)
            return lex_error(ctx, E_OUTOFMEMORY);
        memcpy(unescape_str, ptr, len * sizeof(WCHAR));
        if(!unescape(unescape_str, &len)) {
            WARN("unescape failed\n");
            return lex_error(ctx, E_FAIL);
        }
    }

    if(!(*ret = compiler_alloc_string_len(ctx->compiler, ret_str, len)))
        return lex_error(ctx, E_OUTOFMEMORY);

    /* FIXME: leaking string */
    return tStringLiteral;
}