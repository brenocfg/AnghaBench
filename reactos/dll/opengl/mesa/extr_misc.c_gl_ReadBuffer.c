#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int const DrawBuffer; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* SetBuffer ) (TYPE_5__*,int const) ;} ;
struct TYPE_12__ {int ReadBuffer; } ;
struct TYPE_16__ {TYPE_4__ Color; TYPE_3__ Driver; int /*<<< orphan*/  NewState; TYPE_2__* Buffer; TYPE_1__ Pixel; } ;
struct TYPE_13__ {int /*<<< orphan*/  BackAlpha; int /*<<< orphan*/  Alpha; int /*<<< orphan*/  FrontAlpha; } ;
typedef  int GLenum ;
typedef  TYPE_5__ GLcontext ;

/* Variables and functions */
#define  GL_AUX0 136 
#define  GL_BACK 135 
#define  GL_BACK_LEFT 134 
#define  GL_BACK_RIGHT 133 
 int /*<<< orphan*/  GL_FALSE ; 
#define  GL_FRONT 132 
#define  GL_FRONT_LEFT 131 
#define  GL_FRONT_RIGHT 130 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_LEFT 129 
#define  GL_RIGHT 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_5__*) ; 
 int /*<<< orphan*/  NEW_RASTER_OPS ; 
 int /*<<< orphan*/  gl_error (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int const) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int const) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int const) ; 

void gl_ReadBuffer( GLcontext *ctx, GLenum mode )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glReadBuffer" );
      return;
   }
   switch (mode) {
      case GL_FRONT:
      case GL_FRONT_LEFT:
         if ( (*ctx->Driver.SetBuffer)( ctx, GL_FRONT ) == GL_FALSE) {
            gl_error( ctx, GL_INVALID_ENUM, "glReadBuffer" );
            return;
         }
         ctx->Pixel.ReadBuffer = mode;
         ctx->Buffer->Alpha = ctx->Buffer->FrontAlpha;
         ctx->NewState |= NEW_RASTER_OPS;
         break;
      case GL_BACK:
      case GL_BACK_LEFT:
         if ( (*ctx->Driver.SetBuffer)( ctx, GL_BACK ) == GL_FALSE) {
            gl_error( ctx, GL_INVALID_ENUM, "glReadBuffer" );
            return;
         }
         ctx->Pixel.ReadBuffer = mode;
         ctx->Buffer->Alpha = ctx->Buffer->BackAlpha;
         ctx->NewState |= NEW_RASTER_OPS;
         break;
      case GL_FRONT_RIGHT:
      case GL_BACK_RIGHT:
      case GL_LEFT:
      case GL_RIGHT:
      case GL_AUX0:
         gl_error( ctx, GL_INVALID_OPERATION, "glReadBuffer" );
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glReadBuffer" );
   }

   /* Remember, the draw buffer is the default state */
   (void) (*ctx->Driver.SetBuffer)( ctx, ctx->Color.DrawBuffer );
}