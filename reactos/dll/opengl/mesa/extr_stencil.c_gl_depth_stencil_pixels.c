#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ZPassFunc; int /*<<< orphan*/  ZFailFunc; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* DepthTestPixels ) (TYPE_4__*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*) ;} ;
struct TYPE_8__ {scalar_t__ Test; } ;
struct TYPE_11__ {TYPE_3__ Stencil; TYPE_2__ Driver; TYPE_1__ Depth; } ;
typedef  size_t GLuint ;
typedef  int GLubyte ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLdepth ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_FALSE ; 
 int PB_SIZE ; 
 int /*<<< orphan*/  apply_stencil_op_to_pixels (TYPE_4__*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*) ; 

void gl_depth_stencil_pixels( GLcontext *ctx,
                              GLuint n, const GLint x[], const GLint y[],
			      const GLdepth z[], GLubyte mask[] )
{
   if (ctx->Depth.Test==GL_FALSE) {
      /*
       * No depth buffer, just apply zpass stencil function to active pixels.
       */
      apply_stencil_op_to_pixels( ctx, n, x, y, ctx->Stencil.ZPassFunc, mask );
   }
   else {
      /*
       * Perform depth buffering, then apply zpass or zfail stencil function.
       */
      GLubyte passmask[PB_SIZE], failmask[PB_SIZE], oldmask[PB_SIZE];
      GLuint i;

      /* init pass and fail masks to zero */
      for (i=0;i<n;i++) {
	 passmask[i] = failmask[i] = 0;
         oldmask[i] = mask[i];
      }

      /* apply the depth test */
      if (ctx->Driver.DepthTestPixels)
         (*ctx->Driver.DepthTestPixels)( ctx, n, x, y, z, mask );

      /* set the stencil pass/fail flags according to result of depth test */
      for (i=0;i<n;i++) {
         if (oldmask[i]) {
            if (mask[i]) {
               passmask[i] = 1;
            }
            else {
               failmask[i] = 1;
            }
         }
      }

      /* apply the pass and fail operations */
      apply_stencil_op_to_pixels( ctx, n, x, y,
                                  ctx->Stencil.ZFailFunc, failmask );
      apply_stencil_op_to_pixels( ctx, n, x, y,
                                  ctx->Stencil.ZPassFunc, passmask );
   }

}