#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* ptr; int /*<<< orphan*/  cc_if_depth; int /*<<< orphan*/  ccval; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  char WCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  JS_E_EXPECTED_CCEND ; 
 int /*<<< orphan*/  JS_E_MISSING_LBRACKET ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  check_keyword (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccbool (int /*<<< orphan*/ ) ; 
 int lex_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_cc_expr (TYPE_1__*) ; 
 int /*<<< orphan*/  skip_spaces (TYPE_1__*) ; 
 char* wcschr (char const*,char) ; 

__attribute__((used)) static int skip_code(parser_ctx_t *ctx, BOOL exec_else)
{
    int if_depth = 1;
    const WCHAR *ptr;

    while(1) {
        ptr = wcschr(ctx->ptr, '@');
        if(!ptr) {
            WARN("No @end\n");
            return lex_error(ctx, JS_E_EXPECTED_CCEND);
        }
        ctx->ptr = ptr+1;

        if(!check_keyword(ctx, L"end", NULL)) {
            if(--if_depth)
                continue;
            return 0;
        }

        if(exec_else && !check_keyword(ctx, L"elif", NULL)) {
            if(if_depth > 1)
                continue;

            if(!skip_spaces(ctx) || *ctx->ptr != '(')
                return lex_error(ctx, JS_E_MISSING_LBRACKET);

            if(!parse_cc_expr(ctx))
                return -1;

            if(!get_ccbool(ctx->ccval))
                continue; /* skip block of code */

            /* continue parsing */
            ctx->cc_if_depth++;
            return 0;
        }

        if(exec_else && !check_keyword(ctx, L"else", NULL)) {
            if(if_depth > 1)
                continue;

            /* parse else block */
            ctx->cc_if_depth++;
            return 0;
        }

        if(!check_keyword(ctx, L"if", NULL)) {
            if_depth++;
            continue;
        }

        ctx->ptr++;
    }
}