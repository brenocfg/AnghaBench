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
struct TYPE_5__ {int MapGrid2u1; int MapGrid2un; int MapGrid2u2; int MapGrid2v1; int MapGrid2vn; int MapGrid2v2; } ;
struct TYPE_6__ {TYPE_1__ Eval; } ;
typedef  int GLint ;
typedef  int GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  gl_EvalCoord2f (TYPE_2__*,int,int) ; 

void gl_EvalPoint2( GLcontext* ctx, GLint i, GLint j )
{
	GLfloat u, du;
	GLfloat v, dv;

	if (i==0) {
		u = ctx->Eval.MapGrid2u1;
	}
	else if (i==ctx->Eval.MapGrid2un) {
		u = ctx->Eval.MapGrid2u2;
	}
	else {
		du = (ctx->Eval.MapGrid2u2 - ctx->Eval.MapGrid2u1)
			/ (GLfloat) ctx->Eval.MapGrid2un;
		u = i * du + ctx->Eval.MapGrid2u1;
	}

	if (j==0) {
		v = ctx->Eval.MapGrid2v1;
	}
	else if (j==ctx->Eval.MapGrid2vn) {
		v = ctx->Eval.MapGrid2v2;
	}
	else {
		dv = (ctx->Eval.MapGrid2v2 - ctx->Eval.MapGrid2v1)
			/ (GLfloat) ctx->Eval.MapGrid2vn;
		v = j * dv + ctx->Eval.MapGrid2v1;
	}

	gl_EvalCoord2f( ctx, u, v );
}