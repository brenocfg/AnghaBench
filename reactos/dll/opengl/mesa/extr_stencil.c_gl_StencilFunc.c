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
struct TYPE_6__ {int Function; int /*<<< orphan*/  ValueMask; int /*<<< orphan*/  Ref; } ;
struct TYPE_7__ {TYPE_1__ Stencil; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLint ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (int,int /*<<< orphan*/ ,int) ; 
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
 int STENCIL_BITS ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_StencilFunc( GLcontext *ctx, GLenum func, GLint ref, GLuint mask )
{
   GLint maxref;

   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glStencilFunc" );
      return;
   }

   switch (func) {
      case GL_NEVER:
      case GL_LESS:
      case GL_LEQUAL:
      case GL_GREATER:
      case GL_GEQUAL:
      case GL_EQUAL:
      case GL_NOTEQUAL:
      case GL_ALWAYS:
         ctx->Stencil.Function = func;
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glStencilFunc" );
         return;
   }

   maxref = (1 << STENCIL_BITS) - 1;
   ctx->Stencil.Ref = CLAMP( ref, 0, maxref );
   ctx->Stencil.ValueMask = mask;
}