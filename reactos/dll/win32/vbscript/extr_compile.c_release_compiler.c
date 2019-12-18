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
struct TYPE_3__ {scalar_t__ code; int /*<<< orphan*/  labels; int /*<<< orphan*/  parser; } ;
typedef  TYPE_1__ compile_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_vbscode (scalar_t__) ; 

__attribute__((used)) static void release_compiler(compile_ctx_t *ctx)
{
    parser_release(&ctx->parser);
    heap_free(ctx->labels);
    if(ctx->code)
        release_vbscode(ctx->code);
}