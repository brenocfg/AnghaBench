#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int MapGrid1u1; int MapGrid1un; int MapGrid1u2; } ;
struct TYPE_6__ {TYPE_1__ Eval; } ;
typedef  int GLint ;
typedef  int GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  gl_EvalCoord1f (TYPE_2__*,int) ; 

void gl_EvalPoint1( GLcontext* ctx, GLint i )
{
	GLfloat u, du;

	if (i==0) {
		u = ctx->Eval.MapGrid1u1;
	}
	else if (i==ctx->Eval.MapGrid1un) {
		u = ctx->Eval.MapGrid1u2;
	}
	else {
		du = (ctx->Eval.MapGrid1u2 - ctx->Eval.MapGrid1u1)
			/ (GLfloat) ctx->Eval.MapGrid1un;
		u = i * du + ctx->Eval.MapGrid1u1;
	}
	gl_EvalCoord1f( ctx, u );
}