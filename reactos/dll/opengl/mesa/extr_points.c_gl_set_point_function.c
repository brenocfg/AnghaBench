#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ PointsFunc; } ;
struct TYPE_9__ {double Size; scalar_t__ SmoothFlag; } ;
struct TYPE_8__ {scalar_t__ Enabled; } ;
struct TYPE_11__ {scalar_t__ RenderMode; TYPE_4__ Driver; TYPE_3__ Point; TYPE_2__ Texture; scalar_t__ NoRaster; TYPE_1__* Visual; } ;
struct TYPE_7__ {scalar_t__ RGBAflag; } ;
typedef  TYPE_5__ GLcontext ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 scalar_t__ GL_FEEDBACK ; 
 scalar_t__ GL_RENDER ; 
 scalar_t__ antialiased_rgba_points ; 
 scalar_t__ feedback_points ; 
 scalar_t__ general_ci_points ; 
 scalar_t__ general_rgba_points ; 
 scalar_t__ null_points ; 
 scalar_t__ select_points ; 
 scalar_t__ size1_ci_points ; 
 scalar_t__ size1_rgba_points ; 
 scalar_t__ textured_rgba_points ; 

void gl_set_point_function( GLcontext *ctx )
{
   GLboolean rgbmode = ctx->Visual->RGBAflag;

   if (ctx->RenderMode==GL_RENDER) {
      if (ctx->NoRaster) {
         ctx->Driver.PointsFunc = null_points;
         return;
      }
      if (ctx->Driver.PointsFunc) {
         /* Device driver will draw points. */
         ctx->Driver.PointsFunc = ctx->Driver.PointsFunc;
      }
      else {
         if (ctx->Point.SmoothFlag && rgbmode) {
            ctx->Driver.PointsFunc = antialiased_rgba_points;
         }
         else if (ctx->Texture.Enabled) {
	    ctx->Driver.PointsFunc = textured_rgba_points;
         }
         else if (ctx->Point.Size==1.0) {
            /* size=1, any raster ops */
            if (rgbmode)
               ctx->Driver.PointsFunc = size1_rgba_points;
            else
               ctx->Driver.PointsFunc = size1_ci_points;
         }
         else {
	    /* every other kind of point rendering */
            if (rgbmode)
               ctx->Driver.PointsFunc = general_rgba_points;
            else
               ctx->Driver.PointsFunc = general_ci_points;
         }
      }
   }
   else if (ctx->RenderMode==GL_FEEDBACK) {
      ctx->Driver.PointsFunc = feedback_points;
   }
   else {
      /* GL_SELECT mode */
      ctx->Driver.PointsFunc = select_points;
   }

}