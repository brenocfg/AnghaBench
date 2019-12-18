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
struct TYPE_6__ {int /*<<< orphan*/  EyePlaneQ; int /*<<< orphan*/  ObjectPlaneQ; int /*<<< orphan*/  GenModeQ; int /*<<< orphan*/  EyePlaneR; int /*<<< orphan*/  ObjectPlaneR; int /*<<< orphan*/  GenModeR; int /*<<< orphan*/  EyePlaneT; int /*<<< orphan*/  ObjectPlaneT; int /*<<< orphan*/  GenModeT; int /*<<< orphan*/  EyePlaneS; int /*<<< orphan*/  ObjectPlaneS; int /*<<< orphan*/  GenModeS; } ;
struct TYPE_7__ {TYPE_1__ Texture; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_4V (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENUM_TO_FLOAT (int /*<<< orphan*/ ) ; 
 int GL_EYE_PLANE ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int GL_OBJECT_PLANE ; 
#define  GL_Q 131 
#define  GL_R 130 
#define  GL_S 129 
#define  GL_T 128 
 int GL_TEXTURE_GEN_MODE ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetTexGenfv( GLcontext *ctx,
                     GLenum coord, GLenum pname, GLfloat *params )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glGetTexGenfv" );
      return;
   }

   switch( coord ) {
      case GL_S:
         if (pname==GL_TEXTURE_GEN_MODE) {
            params[0] = ENUM_TO_FLOAT(ctx->Texture.GenModeS);
	 }
	 else if (pname==GL_OBJECT_PLANE) {
            COPY_4V( params, ctx->Texture.ObjectPlaneS );
	 }
	 else if (pname==GL_EYE_PLANE) {
            COPY_4V( params, ctx->Texture.EyePlaneS );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glGetTexGenfv(pname)" );
	    return;
	 }
	 break;
      case GL_T:
         if (pname==GL_TEXTURE_GEN_MODE) {
            params[0] = ENUM_TO_FLOAT(ctx->Texture.GenModeT);
	 }
	 else if (pname==GL_OBJECT_PLANE) {
            COPY_4V( params, ctx->Texture.ObjectPlaneT );
	 }
	 else if (pname==GL_EYE_PLANE) {
            COPY_4V( params, ctx->Texture.EyePlaneT );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glGetTexGenfv(pname)" );
	    return;
	 }
	 break;
      case GL_R:
         if (pname==GL_TEXTURE_GEN_MODE) {
            params[0] = ENUM_TO_FLOAT(ctx->Texture.GenModeR);
	 }
	 else if (pname==GL_OBJECT_PLANE) {
            COPY_4V( params, ctx->Texture.ObjectPlaneR );
	 }
	 else if (pname==GL_EYE_PLANE) {
            COPY_4V( params, ctx->Texture.EyePlaneR );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glGetTexGenfv(pname)" );
	    return;
	 }
	 break;
      case GL_Q:
         if (pname==GL_TEXTURE_GEN_MODE) {
            params[0] = ENUM_TO_FLOAT(ctx->Texture.GenModeQ);
	 }
	 else if (pname==GL_OBJECT_PLANE) {
            COPY_4V( params, ctx->Texture.ObjectPlaneQ );
	 }
	 else if (pname==GL_EYE_PLANE) {
            COPY_4V( params, ctx->Texture.EyePlaneQ );
	 }
	 else {
	    gl_error( ctx, GL_INVALID_ENUM, "glGetTexGenfv(pname)" );
	    return;
	 }
	 break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glGetTexGenfv(coord)" );
	 return;
   }
}