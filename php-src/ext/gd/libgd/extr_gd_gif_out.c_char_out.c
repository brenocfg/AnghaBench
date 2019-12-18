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
struct TYPE_4__ {int* accum; int a_count; } ;
typedef  TYPE_1__ GifCtx ;

/* Variables and functions */
 int /*<<< orphan*/  flush_char (TYPE_1__*) ; 

__attribute__((used)) static void
char_out(int c, GifCtx *ctx)
{
        ctx->accum[ ctx->a_count++ ] = c;
        if( ctx->a_count >= 254 )
                flush_char(ctx);
}