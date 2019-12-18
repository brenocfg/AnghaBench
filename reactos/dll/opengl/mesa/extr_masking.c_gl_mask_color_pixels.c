#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ColorMask; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* ReadColorPixels ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;
struct TYPE_9__ {int RasterMask; TYPE_2__ Color; TYPE_1__ Driver; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLint ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 int ALPHABUF_BIT ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PB_SIZE ; 
 int /*<<< orphan*/  gl_read_alpha_pixels (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void gl_mask_color_pixels( GLcontext *ctx,
                           GLuint n, const GLint x[], const GLint y[],
                           GLubyte red[], GLubyte green[],
                           GLubyte blue[], GLubyte alpha[],
                           const GLubyte mask[] )
{
   GLubyte r[PB_SIZE], g[PB_SIZE], b[PB_SIZE], a[PB_SIZE];

   (*ctx->Driver.ReadColorPixels)( ctx, n, x, y, r, g, b, a, mask );
   if (ctx->RasterMask & ALPHABUF_BIT) {
      gl_read_alpha_pixels( ctx, n, x, y, a, mask );
   }

   if ((ctx->Color.ColorMask & 8) == 0) {
      /* replace source reds with frame buffer reds */
      MEMCPY( red, r, n );
   }
   if ((ctx->Color.ColorMask & 4) == 0) {
      /* replace source greens with frame buffer greens */
      MEMCPY( green, g, n );
   }
   if ((ctx->Color.ColorMask & 2) == 0) {
      /* replace source blues with frame buffer blues */
      MEMCPY( blue, b, n );
   }
   if ((ctx->Color.ColorMask & 1) == 0) {
      /* replace source alphas with frame buffer alphas */
      MEMCPY( alpha, a, n );
   }
}