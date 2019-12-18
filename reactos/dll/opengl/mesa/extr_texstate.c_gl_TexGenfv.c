#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int GenModeS; int GenModeT; int GenModeR; int GenModeQ; int /*<<< orphan*/  EyePlaneQ; int /*<<< orphan*/ * ObjectPlaneQ; int /*<<< orphan*/  EyePlaneR; int /*<<< orphan*/ * ObjectPlaneR; int /*<<< orphan*/  EyePlaneT; int /*<<< orphan*/ * ObjectPlaneT; int /*<<< orphan*/  EyePlaneS; int /*<<< orphan*/ * ObjectPlaneS; } ;
struct TYPE_8__ {int /*<<< orphan*/  NewState; int /*<<< orphan*/  ModelViewInv; TYPE_1__ Texture; int /*<<< orphan*/  NewModelViewMatrix; } ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int GL_EYE_LINEAR ; 
 int GL_EYE_PLANE ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int GL_OBJECT_LINEAR ; 
 int GL_OBJECT_PLANE ; 
#define  GL_Q 131 
#define  GL_R 130 
#define  GL_S 129 
 int GL_SPHERE_MAP ; 
#define  GL_T 128 
 int GL_TEXTURE_GEN_MODE ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_TEXTURING ; 
 int /*<<< orphan*/  gl_analyze_modelview_matrix (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_transform_vector (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void gl_TexGenfv( GLcontext *ctx,
                  GLenum coord, GLenum pname, const GLfloat *params )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glTexGenfv" );
      return;
   }

   switch( coord ) {
      case GL_S:
         if (pname==GL_TEXTURE_GEN_MODE) {
	    GLenum mode = (GLenum) (GLint) *params;
	    if (mode==GL_OBJECT_LINEAR ||
		mode==GL_EYE_LINEAR ||
		mode==GL_SPHERE_MAP) {
	       ctx->Texture.GenModeS = mode;
	    }
	    else {
	       gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(param)" );
	       return;
	    }
	 }
	 else if (pname==GL_OBJECT_PLANE) {
	    ctx->Texture.ObjectPlaneS[0] = params[0];
	    ctx->Texture.ObjectPlaneS[1] = params[1];
	    ctx->Texture.ObjectPlaneS[2] = params[2];
	    ctx->Texture.ObjectPlaneS[3] = params[3];
	 }
	 else if (pname==GL_EYE_PLANE) {
            /* Transform plane equation by the inverse modelview matrix */
            if (ctx->NewModelViewMatrix) {
               gl_analyze_modelview_matrix(ctx);
            }
            gl_transform_vector( ctx->Texture.EyePlaneS, params,
                                 ctx->ModelViewInv );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(pname)" );
	    return;
	 }
	 break;
      case GL_T:
         if (pname==GL_TEXTURE_GEN_MODE) {
	    GLenum mode = (GLenum) (GLint) *params;
	    if (mode==GL_OBJECT_LINEAR ||
		mode==GL_EYE_LINEAR ||
		mode==GL_SPHERE_MAP) {
	       ctx->Texture.GenModeT = mode;
	    }
	    else {
	       gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(param)" );
	       return;
	    }
	 }
	 else if (pname==GL_OBJECT_PLANE) {
	    ctx->Texture.ObjectPlaneT[0] = params[0];
	    ctx->Texture.ObjectPlaneT[1] = params[1];
	    ctx->Texture.ObjectPlaneT[2] = params[2];
	    ctx->Texture.ObjectPlaneT[3] = params[3];
	 }
	 else if (pname==GL_EYE_PLANE) {
            /* Transform plane equation by the inverse modelview matrix */
            if (ctx->NewModelViewMatrix) {
               gl_analyze_modelview_matrix(ctx);
            }
            gl_transform_vector( ctx->Texture.EyePlaneT, params,
                                 ctx->ModelViewInv );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(pname)" );
	    return;
	 }
	 break;
      case GL_R:
         if (pname==GL_TEXTURE_GEN_MODE) {
	    GLenum mode = (GLenum) (GLint) *params;
	    if (mode==GL_OBJECT_LINEAR ||
		mode==GL_EYE_LINEAR) {
	       ctx->Texture.GenModeR = mode;
	    }
	    else {
	       gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(param)" );
	       return;
	    }
	 }
	 else if (pname==GL_OBJECT_PLANE) {
	    ctx->Texture.ObjectPlaneR[0] = params[0];
	    ctx->Texture.ObjectPlaneR[1] = params[1];
	    ctx->Texture.ObjectPlaneR[2] = params[2];
	    ctx->Texture.ObjectPlaneR[3] = params[3];
	 }
	 else if (pname==GL_EYE_PLANE) {
            /* Transform plane equation by the inverse modelview matrix */
            if (ctx->NewModelViewMatrix) {
               gl_analyze_modelview_matrix(ctx);
            }
            gl_transform_vector( ctx->Texture.EyePlaneR, params,
                                 ctx->ModelViewInv );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(pname)" );
	    return;
	 }
	 break;
      case GL_Q:
         if (pname==GL_TEXTURE_GEN_MODE) {
	    GLenum mode = (GLenum) (GLint) *params;
	    if (mode==GL_OBJECT_LINEAR ||
		mode==GL_EYE_LINEAR) {
	       ctx->Texture.GenModeQ = mode;
	    }
	    else {
	       gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(param)" );
	       return;
	    }
	 }
	 else if (pname==GL_OBJECT_PLANE) {
	    ctx->Texture.ObjectPlaneQ[0] = params[0];
	    ctx->Texture.ObjectPlaneQ[1] = params[1];
	    ctx->Texture.ObjectPlaneQ[2] = params[2];
	    ctx->Texture.ObjectPlaneQ[3] = params[3];
	 }
	 else if (pname==GL_EYE_PLANE) {
            /* Transform plane equation by the inverse modelview matrix */
            if (ctx->NewModelViewMatrix) {
               gl_analyze_modelview_matrix(ctx);
            }
            gl_transform_vector( ctx->Texture.EyePlaneQ, params,
                                 ctx->ModelViewInv );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(pname)" );
	    return;
	 }
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glTexGenfv(coord)" );
	 return;
   }

   ctx->NewState |= NEW_TEXTURING;
}