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
typedef  int GLuint ;
typedef  double GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  horner_bezier_curve (double*,double*,double,int,int) ; 

__attribute__((used)) static void
horner_bezier_surf(GLfloat *cn, GLfloat *out, GLfloat u, GLfloat v,
                   GLuint dim, GLuint uorder, GLuint vorder)
{
  GLfloat *cp = cn + uorder*vorder*dim;
  GLuint i, uinc = vorder*dim;

  if(vorder > uorder)
  {
    if(uorder >= 2)
    { 
      GLfloat s, poweru;
      GLuint j, k, bincoeff;

      /* Compute the control polygon for the surface-curve in u-direction */
      for(j=0; j<vorder; j++)
      {
        GLfloat *ucp = &cn[j*dim];

        /* Each control point is the point for parameter u on a */ 
        /* curve defined by the control polygons in u-direction */
	bincoeff = uorder-1;
	s = 1.0-u;

	for(k=0; k<dim; k++)
	  cp[j*dim+k] = s*ucp[k] + bincoeff*u*ucp[uinc+k];

	for(i=2, ucp+=2*uinc, poweru=u*u; i<uorder; 
            i++, poweru*=u, ucp +=uinc)
	{
	  bincoeff *= uorder-i;
          bincoeff /= i;

	  for(k=0; k<dim; k++)
	    cp[j*dim+k] = s*cp[j*dim+k] + bincoeff*poweru*ucp[k];
	}
      }
        
      /* Evaluate curve point in v */
      horner_bezier_curve(cp, out, v, dim, vorder);
    }
    else /* uorder=1 -> cn defines a curve in v */
      horner_bezier_curve(cn, out, v, dim, vorder);
  }
  else /* vorder <= uorder */
  {
    if(vorder > 1)
    {
      GLuint i;

      /* Compute the control polygon for the surface-curve in u-direction */
      for(i=0; i<uorder; i++, cn += uinc)
      {
	/* For constant i all cn[i][j] (j=0..vorder) are located */
	/* on consecutive memory locations, so we can use        */
	/* horner_bezier_curve to compute the control points     */

	horner_bezier_curve(cn, &cp[i*dim], v, dim, vorder);
      }

      /* Evaluate curve point in u */
      horner_bezier_curve(cp, out, u, dim, uorder);
    }
    else  /* vorder=1 -> cn defines a curve in u */
      horner_bezier_curve(cn, out, u, dim, uorder);
  }
}