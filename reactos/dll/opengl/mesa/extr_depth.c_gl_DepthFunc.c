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
struct TYPE_6__ {int Func; } ;
struct TYPE_7__ {int /*<<< orphan*/  NewState; TYPE_1__ Depth; } ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
#define  GL_ALWAYS 135 
#define  GL_EQUAL 134 
#define  GL_GEQUAL 133 
#define  GL_GREATER 132 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_LEQUAL 131 
#define  GL_LESS 130 
#define  GL_NEVER 129 
#define  GL_NOTEQUAL 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_RASTER_OPS ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_DepthFunc( GLcontext* ctx, GLenum func )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glDepthFunc" );
      return;
   }

   switch (func) {
      case GL_NEVER:
      case GL_LESS:    /* (default) pass if incoming z < stored z */
      case GL_GEQUAL:
      case GL_LEQUAL:
      case GL_GREATER:
      case GL_NOTEQUAL:
      case GL_EQUAL:
      case GL_ALWAYS:
         ctx->Depth.Func = func;
         ctx->NewState |= NEW_RASTER_OPS;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glDepth.Func" );
   }
}