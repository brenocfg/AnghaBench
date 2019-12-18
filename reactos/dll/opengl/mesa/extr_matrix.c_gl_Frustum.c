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
struct TYPE_7__ {int /*<<< orphan*/  (* NearFar ) (TYPE_2__*,double,double) ;} ;
struct TYPE_8__ {double** NearFarStack; size_t ProjectionStackDepth; TYPE_1__ Driver; } ;
typedef  double GLfloat ;
typedef  double GLdouble ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 double M (int,int) ; 
 int /*<<< orphan*/  gl_MultMatrixf (TYPE_2__*,double*) ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,double,double) ; 

void gl_Frustum( GLcontext *ctx,
                 GLdouble left, GLdouble right,
	 	 GLdouble bottom, GLdouble top,
		 GLdouble nearval, GLdouble farval )
{
   GLfloat x, y, a, b, c, d;
   GLfloat m[16];

   if (nearval<=0.0 || farval<=0.0) {
      gl_error( ctx,  GL_INVALID_VALUE, "glFrustum(near or far)" );
   }

   x = (2.0*nearval) / (right-left);
   y = (2.0*nearval) / (top-bottom);
   a = (right+left) / (right-left);
   b = (top+bottom) / (top-bottom);
   c = -(farval+nearval) / ( farval-nearval);
   d = -(2.0*farval*nearval) / (farval-nearval);  /* error? */

#define M(row,col)  m[col*4+row]
   M(0,0) = x;     M(0,1) = 0.0F;  M(0,2) = a;      M(0,3) = 0.0F;
   M(1,0) = 0.0F;  M(1,1) = y;     M(1,2) = b;      M(1,3) = 0.0F;
   M(2,0) = 0.0F;  M(2,1) = 0.0F;  M(2,2) = c;      M(2,3) = d;
   M(3,0) = 0.0F;  M(3,1) = 0.0F;  M(3,2) = -1.0F;  M(3,3) = 0.0F;
#undef M

   gl_MultMatrixf( ctx, m );


   /* Need to keep a stack of near/far values in case the user push/pops
    * the projection matrix stack so that we can call Driver.NearFar()
    * after a pop.
    */
   ctx->NearFarStack[ctx->ProjectionStackDepth][0] = nearval;
   ctx->NearFarStack[ctx->ProjectionStackDepth][1] = farval;

   if (ctx->Driver.NearFar) {
      (*ctx->Driver.NearFar)( ctx, nearval, farval );
   }
}