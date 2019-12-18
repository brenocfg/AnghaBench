#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  double GLfloat ;

/* Variables and functions */
 double log (double) ; 

__attribute__((used)) static GLfloat compute_lambda( GLfloat s, GLfloat t,
                               GLfloat dsdx, GLfloat dsdy,
                               GLfloat dtdx, GLfloat dtdy,
                               GLfloat w, GLfloat dwdx, GLfloat dwdy,
                               GLfloat width, GLfloat height ) 
{
   /* TODO: this function can probably be optimized a bit */
   GLfloat invw = 1.0 / w;
   GLfloat dudx, dudy, dvdx, dvdy;
   GLfloat r1, r2, rho2;

   dudx = (dsdx - s*dwdx) * invw * width;
   dudy = (dsdy - s*dwdy) * invw * width;
   dvdx = (dtdx - t*dwdx) * invw * height;
   dvdy = (dtdy - t*dwdy) * invw * height;

   r1 = dudx * dudx + dudy * dudy;
   r2 = dvdx * dvdx + dvdy * dvdy;

   /* rho2 = MAX2(r1,r2); */
   rho2 = r1 + r2;
   if (rho2 <= 0.0F) {
      return 0.0F;
   }
   else {
      /* return log base 2 of rho */
      return log(rho2) * 1.442695 * 0.5;       /* 1.442695 = 1/log(2) */
   }
}