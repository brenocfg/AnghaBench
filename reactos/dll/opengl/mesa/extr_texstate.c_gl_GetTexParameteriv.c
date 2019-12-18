#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* Current2D; TYPE_1__* Current1D; } ;
struct TYPE_10__ {TYPE_3__ Texture; } ;
struct TYPE_8__ {double* BorderColor; int /*<<< orphan*/  Priority; int /*<<< orphan*/  WrapT; int /*<<< orphan*/  WrapS; int /*<<< orphan*/  MinFilter; int /*<<< orphan*/  MagFilter; } ;
struct TYPE_7__ {double* BorderColor; int /*<<< orphan*/  Priority; int /*<<< orphan*/  WrapT; int /*<<< orphan*/  WrapS; int /*<<< orphan*/  MinFilter; int /*<<< orphan*/  MagFilter; } ;
typedef  int /*<<< orphan*/  GLint ;
typedef  double GLfloat ;
typedef  int GLenum ;
typedef  TYPE_4__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  FLOAT_TO_INT (double) ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
#define  GL_TEXTURE_1D 136 
#define  GL_TEXTURE_2D 135 
#define  GL_TEXTURE_BORDER_COLOR 134 
#define  GL_TEXTURE_MAG_FILTER 133 
#define  GL_TEXTURE_MIN_FILTER 132 
#define  GL_TEXTURE_PRIORITY 131 
#define  GL_TEXTURE_RESIDENT 130 
#define  GL_TEXTURE_WRAP_S 129 
#define  GL_TEXTURE_WRAP_T 128 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  gl_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetTexParameteriv( GLcontext *ctx,
                           GLenum target, GLenum pname, GLint *params )
{
   switch (target) {
      case GL_TEXTURE_1D:
         switch (pname) {
	    case GL_TEXTURE_MAG_FILTER:
	       *params = (GLint) ctx->Texture.Current1D->MagFilter;
	       break;
	    case GL_TEXTURE_MIN_FILTER:
	       *params = (GLint) ctx->Texture.Current1D->MinFilter;
	       break;
	    case GL_TEXTURE_WRAP_S:
	       *params = (GLint) ctx->Texture.Current1D->WrapS;
	       break;
	    case GL_TEXTURE_WRAP_T:
	       *params = (GLint) ctx->Texture.Current1D->WrapT;
	       break;
	    case GL_TEXTURE_BORDER_COLOR:
               {
                  GLfloat color[4];
                  color[0] = ctx->Texture.Current1D->BorderColor[0]/255.0;
                  color[1] = ctx->Texture.Current1D->BorderColor[1]/255.0;
                  color[2] = ctx->Texture.Current1D->BorderColor[2]/255.0;
                  color[3] = ctx->Texture.Current1D->BorderColor[3]/255.0;
                  params[0] = FLOAT_TO_INT( color[0] );
                  params[1] = FLOAT_TO_INT( color[1] );
                  params[2] = FLOAT_TO_INT( color[2] );
                  params[3] = FLOAT_TO_INT( color[3] );
               }
	       break;
	    case GL_TEXTURE_RESIDENT:
               *params = (GLint) GL_TRUE;
	       break;
	    case GL_TEXTURE_PRIORITY:
               *params = (GLint) ctx->Texture.Current1D->Priority;
	       break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM, "glGetTexParameteriv(pname)" );
	 }
         break;
      case GL_TEXTURE_2D:
         switch (pname) {
	    case GL_TEXTURE_MAG_FILTER:
	       *params = (GLint) ctx->Texture.Current2D->MagFilter;
	       break;
	    case GL_TEXTURE_MIN_FILTER:
	       *params = (GLint) ctx->Texture.Current2D->MinFilter;
	       break;
	    case GL_TEXTURE_WRAP_S:
	       *params = (GLint) ctx->Texture.Current2D->WrapS;
	       break;
	    case GL_TEXTURE_WRAP_T:
	       *params = (GLint) ctx->Texture.Current2D->WrapT;
	       break;
	    case GL_TEXTURE_BORDER_COLOR:
               {
                  GLfloat color[4];
                  color[0] = ctx->Texture.Current2D->BorderColor[0]/255.0;
                  color[1] = ctx->Texture.Current2D->BorderColor[1]/255.0;
                  color[2] = ctx->Texture.Current2D->BorderColor[2]/255.0;
                  color[3] = ctx->Texture.Current2D->BorderColor[3]/255.0;
                  params[0] = FLOAT_TO_INT( color[0] );
                  params[1] = FLOAT_TO_INT( color[1] );
                  params[2] = FLOAT_TO_INT( color[2] );
                  params[3] = FLOAT_TO_INT( color[3] );
               }
	       break;
	    case GL_TEXTURE_RESIDENT:
               *params = (GLint) GL_TRUE;
	       break;
	    case GL_TEXTURE_PRIORITY:
               *params = (GLint) ctx->Texture.Current2D->Priority;
	       break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM, "glGetTexParameteriv(pname)" );
	 }
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetTexParameteriv(target)" );
   }
}