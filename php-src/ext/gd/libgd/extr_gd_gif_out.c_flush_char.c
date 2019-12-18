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
struct TYPE_3__ {scalar_t__ a_count; int /*<<< orphan*/  g_outfile; int /*<<< orphan*/  accum; } ;
typedef  TYPE_1__ GifCtx ;

/* Variables and functions */
 int /*<<< orphan*/  gdPutBuf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdPutC (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flush_char(GifCtx *ctx)
{
        if( ctx->a_count > 0 ) {
                gdPutC( ctx->a_count, ctx->g_outfile );
                gdPutBuf( ctx->accum, ctx->a_count, ctx->g_outfile );
                ctx->a_count = 0;
        }
}