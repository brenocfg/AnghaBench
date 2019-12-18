#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int BlendSrc; int BlendDst; } ;
struct TYPE_7__ {int /*<<< orphan*/  NewState; TYPE_1__ Color; } ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_DST_ALPHA 138 
#define  GL_DST_COLOR 137 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_ONE 136 
#define  GL_ONE_MINUS_DST_ALPHA 135 
#define  GL_ONE_MINUS_DST_COLOR 134 
#define  GL_ONE_MINUS_SRC_ALPHA 133 
#define  GL_ONE_MINUS_SRC_COLOR 132 
#define  GL_SRC_ALPHA 131 
#define  GL_SRC_ALPHA_SATURATE 130 
#define  GL_SRC_COLOR 129 
#define  GL_ZERO 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_RASTER_OPS ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_BlendFunc( GLcontext* ctx, GLenum sfactor, GLenum dfactor )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glBlendFunc" );
      return;
   }

   switch (sfactor) {
      case GL_ZERO:
      case GL_ONE:
      case GL_DST_COLOR:
      case GL_ONE_MINUS_DST_COLOR:
      case GL_SRC_ALPHA:
      case GL_ONE_MINUS_SRC_ALPHA:
      case GL_DST_ALPHA:
      case GL_ONE_MINUS_DST_ALPHA:
      case GL_SRC_ALPHA_SATURATE:
         ctx->Color.BlendSrc = sfactor;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glBlendFunc(sfactor)" );
         return;
   }

   switch (dfactor) {
      case GL_ZERO:
      case GL_ONE:
      case GL_SRC_COLOR:
      case GL_ONE_MINUS_SRC_COLOR:
      case GL_SRC_ALPHA:
      case GL_ONE_MINUS_SRC_ALPHA:
      case GL_DST_ALPHA:
      case GL_ONE_MINUS_DST_ALPHA:
         ctx->Color.BlendDst = dfactor;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glBlendFunc(dfactor)" );
   }

   ctx->NewState |= NEW_RASTER_OPS;
}