#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  (* SetBuffer ) (TYPE_5__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Clear ) (TYPE_5__*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  Enabled; } ;
struct TYPE_13__ {scalar_t__ SWmasking; } ;
struct TYPE_17__ {int RasterMask; TYPE_4__ Driver; TYPE_3__ Scissor; TYPE_2__* Buffer; TYPE_1__ Color; } ;
struct TYPE_14__ {scalar_t__ Xmin; scalar_t__ Xmax; scalar_t__ Ymin; scalar_t__ Ymax; } ;
typedef  scalar_t__ GLint ;
typedef  TYPE_5__ GLcontext ;

/* Variables and functions */
 int ALPHABUF_BIT ; 
 int FRONT_AND_BACK_BIT ; 
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  clear_color_buffer_with_masking (TYPE_5__*) ; 
 int /*<<< orphan*/  gl_clear_alpha_buffers (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_color_buffers( GLcontext *ctx )
{
   if (ctx->Color.SWmasking) {
      clear_color_buffer_with_masking( ctx );
   }
   else {
      GLint x = ctx->Buffer->Xmin;
      GLint y = ctx->Buffer->Ymin;
      GLint height = ctx->Buffer->Ymax - ctx->Buffer->Ymin + 1;
      GLint width  = ctx->Buffer->Xmax - ctx->Buffer->Xmin + 1;
      (*ctx->Driver.Clear)( ctx, !ctx->Scissor.Enabled,
                            x, y, width, height );
      if (ctx->RasterMask & ALPHABUF_BIT) {
         /* front and/or back alpha buffers will be cleared here */
         gl_clear_alpha_buffers( ctx );
      }
   }

   if (ctx->RasterMask & FRONT_AND_BACK_BIT) {
      /*** Also clear the back buffer ***/
      (*ctx->Driver.SetBuffer)( ctx, GL_BACK );
      if (ctx->Color.SWmasking) {
         clear_color_buffer_with_masking( ctx );
      }
      else {
         GLint x = ctx->Buffer->Xmin;
         GLint y = ctx->Buffer->Ymin;
         GLint height = ctx->Buffer->Ymax - ctx->Buffer->Ymin + 1;
         GLint width  = ctx->Buffer->Xmax - ctx->Buffer->Xmin + 1;
         (*ctx->Driver.Clear)( ctx, !ctx->Scissor.Enabled,
                               x, y, width, height );
      }
      (*ctx->Driver.SetBuffer)( ctx, GL_FRONT );
   }
}