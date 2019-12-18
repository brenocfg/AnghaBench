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
struct TYPE_4__ {char* ptr; char* end; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JS_E_EXPECTED_AT ; 
 int /*<<< orphan*/  JS_E_EXPECTED_IDENTIFIER ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ is_identifier_char (char) ; 
 int /*<<< orphan*/  is_identifier_first_char (char) ; 
 int /*<<< orphan*/  lex_error (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL parse_cc_identifier(parser_ctx_t *ctx, const WCHAR **ret, unsigned *ret_len)
{
    if(*ctx->ptr != '@') {
        lex_error(ctx, JS_E_EXPECTED_AT);
        return FALSE;
    }

    if(!is_identifier_first_char(*++ctx->ptr)) {
        lex_error(ctx, JS_E_EXPECTED_IDENTIFIER);
        return FALSE;
    }

    *ret = ctx->ptr;
    while(++ctx->ptr < ctx->end && is_identifier_char(*ctx->ptr));
    *ret_len = ctx->ptr - *ret;
    return TRUE;
}