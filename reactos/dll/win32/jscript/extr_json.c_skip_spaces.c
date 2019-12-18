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
struct TYPE_3__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ json_parse_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 scalar_t__ is_json_space (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR skip_spaces(json_parse_ctx_t *ctx)
{
    while(is_json_space(*ctx->ptr))
        ctx->ptr++;
    return *ctx->ptr;
}