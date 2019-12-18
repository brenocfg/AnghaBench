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
struct TYPE_4__ {char* ptr; char const* end; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JS_E_MISSING_SEMICOLON ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int hex_to_int (char const) ; 
 scalar_t__ is_identifier_char (char const) ; 
 scalar_t__ iswdigit (char const) ; 
 int /*<<< orphan*/  lex_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_decimal (char const**,char const*,double*) ; 

__attribute__((used)) static BOOL parse_numeric_literal(parser_ctx_t *ctx, double *ret)
{
    HRESULT hres;

    if(*ctx->ptr == '0') {
        ctx->ptr++;

        if(*ctx->ptr == 'x' || *ctx->ptr == 'X') {
            double r = 0;
            int d;
            if(++ctx->ptr == ctx->end) {
                ERR("unexpected end of file\n");
                return FALSE;
            }

            while(ctx->ptr < ctx->end && (d = hex_to_int(*ctx->ptr)) != -1) {
                r = r*16 + d;
                ctx->ptr++;
            }

            if(ctx->ptr < ctx->end && is_identifier_char(*ctx->ptr)) {
                WARN("unexpected identifier char\n");
                lex_error(ctx, JS_E_MISSING_SEMICOLON);
                return FALSE;
            }

            *ret = r;
            return TRUE;
        }

        if(iswdigit(*ctx->ptr)) {
            unsigned base = 8;
            const WCHAR *ptr;
            double val = 0;

            for(ptr = ctx->ptr; ptr < ctx->end && iswdigit(*ptr); ptr++) {
                if(*ptr > '7') {
                    base = 10;
                    break;
                }
            }

            do {
                val = val*base + *ctx->ptr-'0';
            }while(++ctx->ptr < ctx->end && iswdigit(*ctx->ptr));

            /* FIXME: Do we need it here? */
            if(ctx->ptr < ctx->end && (is_identifier_char(*ctx->ptr) || *ctx->ptr == '.')) {
                WARN("wrong char after octal literal: '%c'\n", *ctx->ptr);
                lex_error(ctx, JS_E_MISSING_SEMICOLON);
                return FALSE;
            }

            *ret = val;
            return TRUE;
        }

        if(is_identifier_char(*ctx->ptr)) {
            WARN("wrong char after zero\n");
            lex_error(ctx, JS_E_MISSING_SEMICOLON);
            return FALSE;
        }
    }

    hres = parse_decimal(&ctx->ptr, ctx->end, ret);
    if(FAILED(hres)) {
        lex_error(ctx, hres);
        return FALSE;
    }

    return TRUE;
}