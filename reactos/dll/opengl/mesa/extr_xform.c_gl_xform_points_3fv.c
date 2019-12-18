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
typedef  size_t GLuint ;
typedef  float GLfloat ;

/* Variables and functions */

void gl_xform_points_3fv( GLuint n, GLfloat q[][4], const GLfloat m[16],
                          GLfloat p[][3] )
{
   /* This function has been carefully crafted to maximize register usage
    * and use loop unrolling with IRIX 5.3's cc.  Hopefully other compilers
    * will like this code too.
    */
   {
      GLuint i;
      GLfloat m0 = m[0],  m4 = m[4],  m8 = m[8],  m12 = m[12];
      GLfloat m1 = m[1],  m5 = m[5],  m9 = m[9],  m13 = m[13];
      for (i=0;i<n;i++) {
         GLfloat p0 = p[i][0], p1 = p[i][1], p2 = p[i][2];
         q[i][0] = m0 * p0 + m4  * p1 + m8 * p2 + m12;
         q[i][1] = m1 * p0 + m5  * p1 + m9 * p2 + m13;
      }
   }
   {
      GLuint i;
      GLfloat m2 = m[2],  m6 = m[6],  m10 = m[10],  m14 = m[14];
      GLfloat m3 = m[3],  m7 = m[7],  m11 = m[11],  m15 = m[15];
      if (m3==0.0F && m7==0.0F && m11==0.0F && m15==1.0F) {
         /* common case */
         for (i=0;i<n;i++) {
            GLfloat p0 = p[i][0], p1 = p[i][1], p2 = p[i][2];
            q[i][2] = m2 * p0 + m6 * p1 + m10 * p2 + m14;
            q[i][3] = 1.0F;
         }
      }
      else {
         /* general case */
         for (i=0;i<n;i++) {
            GLfloat p0 = p[i][0], p1 = p[i][1], p2 = p[i][2];
            q[i][2] = m2 * p0 + m6 * p1 + m10 * p2 + m14;
            q[i][3] = m3 * p0 + m7 * p1 + m11 * p2 + m15;
         }
      }
   }
}