#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int MapRtoRsize; int MapGtoGsize; int MapBtoBsize; int MapAtoAsize; int* MapRtoR; int* MapGtoG; int* MapBtoB; int* MapAtoA; } ;
struct TYPE_5__ {TYPE_1__ Pixel; } ;
typedef  size_t GLint ;
typedef  int GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */

__attribute__((used)) static void map_rgba( GLcontext *ctx,
                      GLint n,
		      GLfloat red[], GLfloat green[],
		      GLfloat blue[], GLfloat alpha[] )
{
   GLfloat rscale = ctx->Pixel.MapRtoRsize-1;
   GLfloat gscale = ctx->Pixel.MapGtoGsize-1;
   GLfloat bscale = ctx->Pixel.MapBtoBsize-1;
   GLfloat ascale = ctx->Pixel.MapAtoAsize-1;
   GLint i;

   for (i=0;i<n;i++) {
      red[i]   = ctx->Pixel.MapRtoR[ (GLint) (red[i]   * rscale) ];
      green[i] = ctx->Pixel.MapGtoG[ (GLint) (green[i] * gscale) ];
      blue[i]  = ctx->Pixel.MapBtoB[ (GLint) (blue[i]  * bscale) ];
      alpha[i] = ctx->Pixel.MapAtoA[ (GLint) (alpha[i] * ascale) ];
   }
}