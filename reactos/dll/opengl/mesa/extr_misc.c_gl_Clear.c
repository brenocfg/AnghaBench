#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  (* ClearDepthBuffer ) (TYPE_4__*) ;int /*<<< orphan*/  (* SetBuffer ) (TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ClearColorAndDepth ) (TYPE_4__*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  Enabled; } ;
struct TYPE_20__ {scalar_t__ RenderMode; int RasterMask; int /*<<< orphan*/  ClearCount; int /*<<< orphan*/  ClearTime; TYPE_3__ Driver; TYPE_2__ Scissor; TYPE_1__* Buffer; scalar_t__ NewState; } ;
struct TYPE_17__ {scalar_t__ Xmin; scalar_t__ Xmax; scalar_t__ Ymin; scalar_t__ Ymax; } ;
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLdouble ;
typedef  TYPE_4__ GLcontext ;
typedef  int GLbitfield ;

/* Variables and functions */
 int FRONT_AND_BACK_BIT ; 
 int GL_ACCUM_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_BACK ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ GL_RENDER ; 
 int GL_STENCIL_BUFFER_BIT ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_4__*) ; 
 int /*<<< orphan*/  clear_color_buffers (TYPE_4__*) ; 
 int /*<<< orphan*/  gl_clear_accum_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  gl_clear_stencil_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gl_time () ; 
 int /*<<< orphan*/  gl_update_state (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*) ; 

void gl_Clear( GLcontext *ctx, GLbitfield mask )
{
#ifdef PROFILE
   GLdouble t0 = gl_time();
#endif

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glClear" );
      return;
   }

   if (ctx->RenderMode==GL_RENDER) {
      if (ctx->NewState) {
         gl_update_state( ctx );
      }

      /* See if we can call device driver function to clear both the
       * color and depth buffers.
       */
      if (ctx->Driver.ClearColorAndDepth &&
          (mask & GL_COLOR_BUFFER_BIT) && (mask & GL_DEPTH_BUFFER_BIT)) {
         GLint x = ctx->Buffer->Xmin;
         GLint y = ctx->Buffer->Ymin;
         GLint height = ctx->Buffer->Ymax - ctx->Buffer->Ymin + 1;
         GLint width  = ctx->Buffer->Xmax - ctx->Buffer->Xmin + 1;
         (*ctx->Driver.ClearColorAndDepth)( ctx, !ctx->Scissor.Enabled,
                                            x, y, width, height );
         if (ctx->RasterMask & FRONT_AND_BACK_BIT) {
            /*** Also clear the back buffer ***/
            (*ctx->Driver.SetBuffer)( ctx, GL_BACK );
            (*ctx->Driver.ClearColorAndDepth)( ctx, !ctx->Scissor.Enabled,
                                               x, y, width, height );
            (*ctx->Driver.SetBuffer)( ctx, GL_FRONT );
         }
      }
      else {
         /* normal procedure for clearing buffers */
         if (mask & GL_COLOR_BUFFER_BIT)  clear_color_buffers( ctx );
         if (mask & GL_DEPTH_BUFFER_BIT)  (*ctx->Driver.ClearDepthBuffer)(ctx);
         if (mask & GL_ACCUM_BUFFER_BIT)   gl_clear_accum_buffer( ctx );
         if (mask & GL_STENCIL_BUFFER_BIT) gl_clear_stencil_buffer( ctx );
      }

#ifdef PROFILE
      ctx->ClearTime += gl_time() - t0;
      ctx->ClearCount++;
#endif
   }
}