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
typedef  float real ;
typedef  int integer ;

/* Variables and functions */
 int /*<<< orphan*/  dabs (float) ; 
 float sqrt (float) ; 

int slaed5_(integer *i__, real *d__, real *z__, real *delta,
	real *rho, real *dlam)
{
    /* System generated locals */
    real r__1;

    /* Local variables */
    static real b, c__, w, del, tau, temp;


/*
    -- LAPACK routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    This subroutine computes the I-th eigenvalue of a symmetric rank-one
    modification of a 2-by-2 diagonal matrix

               diag( D )  +  RHO *  Z * transpose(Z) .

    The diagonal elements in the array D are assumed to satisfy

               D(i) < D(j)  for  i < j .

    We also assume RHO > 0 and that the Euclidean norm of the vector
    Z is one.

    Arguments
    =========

    I      (input) INTEGER
           The index of the eigenvalue to be computed.  I = 1 or I = 2.

    D      (input) REAL array, dimension (2)
           The original eigenvalues.  We assume D(1) < D(2).

    Z      (input) REAL array, dimension (2)
           The components of the updating vector.

    DELTA  (output) REAL array, dimension (2)
           The vector DELTA contains the information necessary
           to construct the eigenvectors.

    RHO    (input) REAL
           The scalar in the symmetric updating formula.

    DLAM   (output) REAL
           The computed lambda_I, the I-th updated eigenvalue.

    Further Details
    ===============

    Based on contributions by
       Ren-Cang Li, Computer Science Division, University of California
       at Berkeley, USA

    =====================================================================
*/


    /* Parameter adjustments */
    --delta;
    --z__;
    --d__;

    /* Function Body */
    del = d__[2] - d__[1];
    if (*i__ == 1) {
	w = *rho * 2.f * (z__[2] * z__[2] - z__[1] * z__[1]) / del + 1.f;
	if (w > 0.f) {
	    b = del + *rho * (z__[1] * z__[1] + z__[2] * z__[2]);
	    c__ = *rho * z__[1] * z__[1] * del;

/*           B > ZERO, always */

	    tau = c__ * 2.f / (b + sqrt((r__1 = b * b - c__ * 4.f, dabs(r__1))
		    ));
	    *dlam = d__[1] + tau;
	    delta[1] = -z__[1] / tau;
	    delta[2] = z__[2] / (del - tau);
	} else {
	    b = -del + *rho * (z__[1] * z__[1] + z__[2] * z__[2]);
	    c__ = *rho * z__[2] * z__[2] * del;
	    if (b > 0.f) {
		tau = c__ * -2.f / (b + sqrt(b * b + c__ * 4.f));
	    } else {
		tau = (b - sqrt(b * b + c__ * 4.f)) / 2.f;
	    }
	    *dlam = d__[2] + tau;
	    delta[1] = -z__[1] / (del + tau);
	    delta[2] = -z__[2] / tau;
	}
	temp = sqrt(delta[1] * delta[1] + delta[2] * delta[2]);
	delta[1] /= temp;
	delta[2] /= temp;
    } else {

/*     Now I=2 */

	b = -del + *rho * (z__[1] * z__[1] + z__[2] * z__[2]);
	c__ = *rho * z__[2] * z__[2] * del;
	if (b > 0.f) {
	    tau = (b + sqrt(b * b + c__ * 4.f)) / 2.f;
	} else {
	    tau = c__ * 2.f / (-b + sqrt(b * b + c__ * 4.f));
	}
	*dlam = d__[2] + tau;
	delta[1] = -z__[1] / (del + tau);
	delta[2] = -z__[2] / tau;
	temp = sqrt(delta[1] * delta[1] + delta[2] * delta[2]);
	delta[1] /= temp;
	delta[2] /= temp;
    }
    return 0;

/*     End OF SLAED5 */

}