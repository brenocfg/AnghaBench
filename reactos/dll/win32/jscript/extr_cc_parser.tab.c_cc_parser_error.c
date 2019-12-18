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
struct TYPE_3__ {int /*<<< orphan*/  hres; } ;
typedef  TYPE_1__ parser_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  JS_E_SYNTAX ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,char const*) ; 

__attribute__((used)) static int cc_parser_error(parser_ctx_t *ctx, const char *str)
{
    if(SUCCEEDED(ctx->hres)) {
        WARN("%s\n", str);
        ctx->hres = JS_E_SYNTAX;
    }

    return 0;
}