#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float* ModelViewMatrix; int /*<<< orphan*/  NewModelViewMatrix; int /*<<< orphan*/  ModelViewInv; int /*<<< orphan*/  ModelViewMatrixType; } ;
typedef  float GLfloat ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  MATRIX_2D ; 
 int /*<<< orphan*/  MATRIX_2D_NO_ROT ; 
 int /*<<< orphan*/  MATRIX_3D ; 
 int /*<<< orphan*/  MATRIX_GENERAL ; 
 int /*<<< orphan*/  MATRIX_IDENTITY ; 
 int /*<<< orphan*/  invert_matrix (float*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_identity (float const*) ; 

void gl_analyze_modelview_matrix( GLcontext *ctx )
{
   const GLfloat *m = ctx->ModelViewMatrix;
   if (is_identity(m)) {
      ctx->ModelViewMatrixType = MATRIX_IDENTITY;
   }
   else if (                 m[4]==0.0F && m[ 8]==0.0F               
            && m[1]==0.0F               && m[ 9]==0.0F
            && m[2]==0.0F && m[6]==0.0F && m[10]==1.0F && m[14]==0.0F
            && m[3]==0.0F && m[7]==0.0F && m[11]==0.0F && m[15]==1.0F) {
      ctx->ModelViewMatrixType = MATRIX_2D_NO_ROT;
   }
   else if (                               m[ 8]==0.0F               
            &&                             m[ 9]==0.0F
            && m[2]==0.0F && m[6]==0.0F && m[10]==1.0F && m[14]==0.0F
            && m[3]==0.0F && m[7]==0.0F && m[11]==0.0F && m[15]==1.0F) {
      ctx->ModelViewMatrixType = MATRIX_2D;
   }
   else if (m[3]==0.0F && m[7]==0.0F && m[11]==0.0F && m[15]==1.0F) {
      ctx->ModelViewMatrixType = MATRIX_3D;
   }
   else {
      ctx->ModelViewMatrixType = MATRIX_GENERAL;
   }

   invert_matrix( ctx->ModelViewMatrix, ctx->ModelViewInv );
   ctx->NewModelViewMatrix = GL_FALSE;
}