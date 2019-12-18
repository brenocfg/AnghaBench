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
struct TYPE_6__ {int MapGrid2un; int MapGrid2vn; void* MapGrid2v2; void* MapGrid2v1; void* MapGrid2u2; void* MapGrid2u1; } ;
struct TYPE_7__ {TYPE_1__ Eval; } ;
typedef  int GLint ;
typedef  void* GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_MapGrid2f( GLcontext* ctx, GLint un, GLfloat u1, GLfloat u2,
		  GLint vn, GLfloat v1, GLfloat v2 )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glMapGrid2f" );
      return;
   }
   if (un<1) {
      gl_error( ctx, GL_INVALID_VALUE, "glMapGrid2f(un)" );
      return;
   }
   if (vn<1) {
      gl_error( ctx, GL_INVALID_VALUE, "glMapGrid2f(vn)" );
      return;
   }
   ctx->Eval.MapGrid2un = un;
   ctx->Eval.MapGrid2u1 = u1;
   ctx->Eval.MapGrid2u2 = u2;
   ctx->Eval.MapGrid2vn = vn;
   ctx->Eval.MapGrid2v1 = v1;
   ctx->Eval.MapGrid2v2 = v2;
}