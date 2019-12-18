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
struct TYPE_3__ {float* ProjectionMatrix; int /*<<< orphan*/  NewProjectionMatrix; int /*<<< orphan*/  ProjectionMatrixType; } ;
typedef  float GLfloat ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  MATRIX_GENERAL ; 
 int /*<<< orphan*/  MATRIX_IDENTITY ; 
 int /*<<< orphan*/  MATRIX_ORTHO ; 
 int /*<<< orphan*/  MATRIX_PERSPECTIVE ; 
 scalar_t__ is_identity (float const*) ; 

void gl_analyze_projection_matrix( GLcontext *ctx )
{
   /* look for common-case ortho and perspective matrices */
   const GLfloat *m = ctx->ProjectionMatrix;
   if (is_identity(m)) {
      ctx->ProjectionMatrixType = MATRIX_IDENTITY;
   }
   else if (                 m[4]==0.0F && m[8] ==0.0F
            && m[1]==0.0F               && m[9] ==0.0F
            && m[2]==0.0F && m[6]==0.0F
            && m[3]==0.0F && m[7]==0.0F && m[11]==0.0F && m[15]==1.0F) {
      ctx->ProjectionMatrixType = MATRIX_ORTHO;
   }
   else if (                 m[4]==0.0F                 && m[12]==0.0F
            && m[1]==0.0F                               && m[13]==0.0F
            && m[2]==0.0F && m[6]==0.0F
            && m[3]==0.0F && m[7]==0.0F && m[11]==-1.0F && m[15]==0.0F) {
      ctx->ProjectionMatrixType = MATRIX_PERSPECTIVE;
   }
   else {
      ctx->ProjectionMatrixType = MATRIX_GENERAL;
   }

   ctx->NewProjectionMatrix = GL_FALSE;
}