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
typedef  float GLfloat ;
typedef  double GLdouble ;

/* Variables and functions */
 double pow (float,float) ; 

__attribute__((used)) static GLfloat gl_pow( GLfloat x, GLfloat y )
{
   GLdouble z = pow(x, y);
   if (z<1.0e-10)
      return 0.0F;
   else
      return (GLfloat) z;
}