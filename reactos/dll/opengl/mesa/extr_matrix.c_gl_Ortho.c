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
struct TYPE_6__ {int /*<<< orphan*/  (* NearFar ) (TYPE_2__*,double,double) ;} ;
struct TYPE_7__ {TYPE_1__ Driver; } ;
typedef  double GLfloat ;
typedef  double GLdouble ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 double M (int,int) ; 
 int /*<<< orphan*/  gl_MultMatrixf (TYPE_2__*,double*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,double,double) ; 

void gl_Ortho( GLcontext *ctx,
               GLdouble left, GLdouble right,
               GLdouble bottom, GLdouble top,
               GLdouble nearval, GLdouble farval )
{
   GLfloat x, y, z;
   GLfloat tx, ty, tz;
   GLfloat m[16];

   x = 2.0 / (right-left);
   y = 2.0 / (top-bottom);
   z = -2.0 / (farval-nearval);
   tx = -(right+left) / (right-left);
   ty = -(top+bottom) / (top-bottom);
   tz = -(farval+nearval) / (farval-nearval);

#define M(row,col)  m[col*4+row]
   M(0,0) = x;     M(0,1) = 0.0F;  M(0,2) = 0.0F;  M(0,3) = tx;
   M(1,0) = 0.0F;  M(1,1) = y;     M(1,2) = 0.0F;  M(1,3) = ty;
   M(2,0) = 0.0F;  M(2,1) = 0.0F;  M(2,2) = z;     M(2,3) = tz;
   M(3,0) = 0.0F;  M(3,1) = 0.0F;  M(3,2) = 0.0F;  M(3,3) = 1.0F;
#undef M

   gl_MultMatrixf( ctx, m );

   if (ctx->Driver.NearFar) {
      (*ctx->Driver.NearFar)( ctx, nearval, farval );
   }
}