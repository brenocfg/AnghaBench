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
struct TYPE_5__ {int nl; scalar_t__ ptr; scalar_t__ begin; } ;
typedef  TYPE_1__ parser_ctx_t ;

/* Variables and functions */
 int cc_token (TYPE_1__*,void*) ; 
 int next_token (TYPE_1__*,void*) ; 

int parser_lex(void *lval, parser_ctx_t *ctx)
{
    int ret;

    ctx->nl = ctx->ptr == ctx->begin;

    do {
        ret = next_token(ctx, lval);
    } while(ret == '@' && !(ret = cc_token(ctx, lval)));

    return ret;
}