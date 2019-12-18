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
struct TYPE_3__ {scalar_t__ curx; scalar_t__ Width; int cury; int Pass; int Height; int /*<<< orphan*/  Interlace; } ;
typedef  TYPE_1__ GifCtx ;

/* Variables and functions */

__attribute__((used)) static void
BumpPixel(GifCtx *ctx)
{
        /*
         * Bump the current X position
         */
        ++(ctx->curx);

        /*
         * If we are at the end of a scan line, set curx back to the beginning
         * If we are interlaced, bump the cury to the appropriate spot,
         * otherwise, just increment it.
         */
        if( ctx->curx == ctx->Width ) {
                ctx->curx = 0;

                if( !ctx->Interlace )
                        ++(ctx->cury);
                else {
                     switch( ctx->Pass ) {

                       case 0:
                          ctx->cury += 8;
                          if( ctx->cury >= ctx->Height ) {
                                ++(ctx->Pass);
                                ctx->cury = 4;
                          }
                          break;

                       case 1:
                          ctx->cury += 8;
                          if( ctx->cury >= ctx->Height ) {
                                ++(ctx->Pass);
                                ctx->cury = 2;
                          }
                          break;

                       case 2:
                          ctx->cury += 4;
                          if( ctx->cury >= ctx->Height ) {
                             ++(ctx->Pass);
                             ctx->cury = 1;
                          }
                          break;

                       case 3:
                          ctx->cury += 2;
                          break;
                        }
                }
        }
}