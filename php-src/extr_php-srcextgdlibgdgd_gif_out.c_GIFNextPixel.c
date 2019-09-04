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
typedef  int /*<<< orphan*/  gdImagePtr ;
struct TYPE_4__ {scalar_t__ CountDown; int /*<<< orphan*/  cury; int /*<<< orphan*/  curx; } ;
typedef  TYPE_1__ GifCtx ;

/* Variables and functions */
 int /*<<< orphan*/  BumpPixel (TYPE_1__*) ; 
 int EOF ; 
 int gdImageGetPixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
GIFNextPixel(gdImagePtr im, GifCtx *ctx)
{
        int r;

        if( ctx->CountDown == 0 )
                return EOF;

        --(ctx->CountDown);

        r = gdImageGetPixel(im, ctx->curx, ctx->cury);

        BumpPixel(ctx);

        return r;
}