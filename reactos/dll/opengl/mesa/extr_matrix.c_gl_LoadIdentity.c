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
struct TYPE_7__ {int MatrixMode; } ;
struct TYPE_8__ {void* NewTextureMatrix; void* TextureMatrixType; int /*<<< orphan*/  TextureMatrix; void* NewProjectionMatrix; void* ProjectionMatrixType; int /*<<< orphan*/  ProjectionMatrix; void* NewModelViewMatrix; void* ModelViewMatrixType; int /*<<< orphan*/  ModelViewInv; int /*<<< orphan*/  ModelViewMatrix; TYPE_1__ Transform; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 void* GL_FALSE ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
#define  GL_MODELVIEW 130 
#define  GL_PROJECTION 129 
#define  GL_TEXTURE 128 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  Identity ; 
 void* MATRIX_IDENTITY ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_problem (TYPE_2__*,char*) ; 

void gl_LoadIdentity( GLcontext *ctx )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx,  GL_INVALID_OPERATION, "glLoadIdentity" );
      return;
   }
   switch (ctx->Transform.MatrixMode) {
      case GL_MODELVIEW:
         MEMCPY( ctx->ModelViewMatrix, Identity, 16*sizeof(GLfloat) );
         MEMCPY( ctx->ModelViewInv, Identity, 16*sizeof(GLfloat) );
         ctx->ModelViewMatrixType = MATRIX_IDENTITY;
	 ctx->NewModelViewMatrix = GL_FALSE;
	 break;
      case GL_PROJECTION:
	 MEMCPY( ctx->ProjectionMatrix, Identity, 16*sizeof(GLfloat) );
         ctx->ProjectionMatrixType = MATRIX_IDENTITY;
	 ctx->NewProjectionMatrix = GL_FALSE;
	 break;
      case GL_TEXTURE:
	 MEMCPY( ctx->TextureMatrix, Identity, 16*sizeof(GLfloat) );
         ctx->TextureMatrixType = MATRIX_IDENTITY;
	 ctx->NewTextureMatrix = GL_FALSE;
	 break;
      default:
         gl_problem(ctx, "Bad matrix mode in gl_LoadIdentity");
   }
}