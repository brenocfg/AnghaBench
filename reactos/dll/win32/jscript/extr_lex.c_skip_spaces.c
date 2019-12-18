#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* ptr; int* end; int /*<<< orphan*/  nl; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ is_endline (int /*<<< orphan*/ ) ; 
 scalar_t__ iswspace (int) ; 

__attribute__((used)) static BOOL skip_spaces(parser_ctx_t *ctx)
{
    while(ctx->ptr < ctx->end && (iswspace(*ctx->ptr) || *ctx->ptr == 0xFEFF /* UTF16 BOM */)) {
        if(is_endline(*ctx->ptr++))
            ctx->nl = TRUE;
    }

    return ctx->ptr != ctx->end;
}