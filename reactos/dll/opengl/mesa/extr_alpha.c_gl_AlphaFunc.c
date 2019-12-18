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
struct TYPE_8__ {int AlphaFunc; int AlphaRef; int /*<<< orphan*/  AlphaRefUbyte; } ;
struct TYPE_9__ {TYPE_1__* Visual; TYPE_2__ Color; } ;
struct TYPE_7__ {int AlphaScale; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int GLenum ;
typedef  TYPE_3__ GLcontext ;
typedef  int /*<<< orphan*/  GLclampf ;

/* Variables and functions */
 int CLAMP (int /*<<< orphan*/ ,float,float) ; 
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
 scalar_t__ INSIDE_BEGIN_END (TYPE_3__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

void gl_AlphaFunc( GLcontext* ctx, GLenum func, GLclampf ref )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glAlphaFunc" );
      return;
   }
   switch (func) {
      case GL_NEVER:
      case GL_LESS:
      case GL_EQUAL:
      case GL_LEQUAL:
      case GL_GREATER:
      case GL_NOTEQUAL:
      case GL_GEQUAL:
      case GL_ALWAYS:
         ctx->Color.AlphaFunc = func;
         ctx->Color.AlphaRef = CLAMP( ref, 0.0F, 1.0F );
         ctx->Color.AlphaRefUbyte = (GLubyte) (ctx->Color.AlphaRef
                                              * ctx->Visual->AlphaScale);
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glAlphaFunc(func)" );
         break;
   }
}