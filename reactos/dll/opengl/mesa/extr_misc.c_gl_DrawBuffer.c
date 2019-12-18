#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int DrawBuffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* SetBuffer ) (TYPE_4__*,int const) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  NewState; TYPE_3__* Buffer; TYPE_2__ Color; TYPE_1__ Driver; } ;
struct TYPE_12__ {int /*<<< orphan*/ * Alpha; int /*<<< orphan*/ * BackAlpha; int /*<<< orphan*/ * FrontAlpha; } ;
typedef  int GLenum ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
#define  GL_AUX0 138 
#define  GL_BACK 137 
#define  GL_BACK_LEFT 136 
#define  GL_BACK_RIGHT 135 
 int /*<<< orphan*/  GL_FALSE ; 
#define  GL_FRONT 134 
#define  GL_FRONT_AND_BACK 133 
#define  GL_FRONT_LEFT 132 
#define  GL_FRONT_RIGHT 131 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_LEFT 130 
#define  GL_NONE 129 
#define  GL_RIGHT 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_4__*) ; 
 int /*<<< orphan*/  NEW_RASTER_OPS ; 
 int /*<<< orphan*/  gl_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int const) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int const) ; 

void gl_DrawBuffer( GLcontext *ctx, GLenum mode )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glDrawBuffer" );
      return;
   }
   switch (mode) {
      case GL_FRONT:
      case GL_FRONT_LEFT:
      case GL_FRONT_AND_BACK:
         if ( (*ctx->Driver.SetBuffer)( ctx, GL_FRONT ) == GL_FALSE ) {
            gl_error( ctx, GL_INVALID_ENUM, "glDrawBuffer" );
            return;
         }
         ctx->Color.DrawBuffer = mode;
         ctx->Buffer->Alpha = ctx->Buffer->FrontAlpha;
	 ctx->NewState |= NEW_RASTER_OPS;
         break;
      case GL_BACK:
      case GL_BACK_LEFT:
         if ( (*ctx->Driver.SetBuffer)( ctx, GL_BACK ) == GL_FALSE) {
            gl_error( ctx, GL_INVALID_ENUM, "glDrawBuffer" );
            return;
         }
         ctx->Color.DrawBuffer = mode;
         ctx->Buffer->Alpha = ctx->Buffer->BackAlpha;
	 ctx->NewState |= NEW_RASTER_OPS;
         break;
      case GL_NONE:
         ctx->Color.DrawBuffer = mode;
         ctx->Buffer->Alpha = NULL;
         ctx->NewState |= NEW_RASTER_OPS;
         break;
      case GL_FRONT_RIGHT:
      case GL_BACK_RIGHT:
      case GL_LEFT:
      case GL_RIGHT:
      case GL_AUX0:
         gl_error( ctx, GL_INVALID_OPERATION, "glDrawBuffer" );
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glDrawBuffer" );
   }
}