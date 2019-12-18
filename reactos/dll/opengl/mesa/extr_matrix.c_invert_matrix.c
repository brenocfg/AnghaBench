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

/* Variables and functions */
 float* Identity ; 
 int /*<<< orphan*/  MEMCPY (float*,float*,int) ; 
 int /*<<< orphan*/  invert_matrix_general (float const*,float*) ; 
 float m11 ; 
 float m12 ; 
 float m13 ; 
 float m14 ; 
 float m21 ; 
 float m22 ; 
 float m23 ; 
 float m24 ; 
 float m31 ; 
 float m32 ; 
 float m33 ; 
 float m34 ; 
 int m41 ; 
 int m42 ; 
 int m43 ; 
 int m44 ; 

__attribute__((used)) static void invert_matrix( const GLfloat *m, GLfloat *out )
{
/* NB. OpenGL Matrices are COLUMN major. */
#define MAT(m,r,c) (m)[(c)*4+(r)]

/* Here's some shorthand converting standard (row,column) to index. */
#define m11 MAT(m,0,0)
#define m12 MAT(m,0,1)
#define m13 MAT(m,0,2)
#define m14 MAT(m,0,3)
#define m21 MAT(m,1,0)
#define m22 MAT(m,1,1)
#define m23 MAT(m,1,2)
#define m24 MAT(m,1,3)
#define m31 MAT(m,2,0)
#define m32 MAT(m,2,1)
#define m33 MAT(m,2,2)
#define m34 MAT(m,2,3)
#define m41 MAT(m,3,0)
#define m42 MAT(m,3,1)
#define m43 MAT(m,3,2)
#define m44 MAT(m,3,3)

   register GLfloat det;
   GLfloat tmp[16]; /* Allow out == in. */

   if( m41 != 0. || m42 != 0. || m43 != 0. || m44 != 1. ) {
      invert_matrix_general(m, out);
      return;
   }

   /* Inverse = adjoint / det. (See linear algebra texts.)*/

   tmp[0]= m22 * m33 - m23 * m32;
   tmp[1]= m23 * m31 - m21 * m33;
   tmp[2]= m21 * m32 - m22 * m31;

   /* Compute determinant as early as possible using these cofactors. */
   det= m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2];

   /* Run singularity test. */
   if (det == 0.0F) {
      /* printf("invert_matrix: Warning: Singular matrix.\n"); */
      MEMCPY( out, Identity, 16*sizeof(GLfloat) );
   }
   else {
      GLfloat d12, d13, d23, d24, d34, d41;
      register GLfloat im11, im12, im13, im14;

      det= 1. / det;

      /* Compute rest of inverse. */
      tmp[0] *= det;
      tmp[1] *= det;
      tmp[2] *= det;
      tmp[3]  = 0.;

      im11= m11 * det;
      im12= m12 * det;
      im13= m13 * det;
      im14= m14 * det;
      tmp[4] = im13 * m32 - im12 * m33;
      tmp[5] = im11 * m33 - im13 * m31;
      tmp[6] = im12 * m31 - im11 * m32;
      tmp[7] = 0.;

      /* Pre-compute 2x2 dets for first two rows when computing */
      /* cofactors of last two rows. */
      d12 = im11*m22 - m21*im12;
      d13 = im11*m23 - m21*im13;
      d23 = im12*m23 - m22*im13;
      d24 = im12*m24 - m22*im14;
      d34 = im13*m24 - m23*im14;
      d41 = im14*m21 - m24*im11;

      tmp[8] =  d23;
      tmp[9] = -d13;
      tmp[10] = d12;
      tmp[11] = 0.;

      tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23);
      tmp[13] =  (m31 * d34 + m33 * d41 + m34 * d13);
      tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12);
      tmp[15] =  1.;

      MEMCPY(out, tmp, 16*sizeof(GLfloat));
  }

#undef m11
#undef m12
#undef m13
#undef m14
#undef m21
#undef m22
#undef m23
#undef m24
#undef m31
#undef m32
#undef m33
#undef m34
#undef m41
#undef m42
#undef m43
#undef m44
#undef MAT
}