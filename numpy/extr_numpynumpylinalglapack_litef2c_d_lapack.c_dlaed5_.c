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
typedef  int integer ;
typedef  int doublereal ;

/* Variables and functions */
 int /*<<< orphan*/  abs (int) ; 
 int sqrt (int) ; 

int dlaed5_(integer *i__, doublereal *d__, doublereal *z__,
	doublereal *delta, doublereal *rho, doublereal *dlam)
{
    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    static doublereal b, c__, w, del, tau, temp;


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

    D      (input) DOUBLE PRECISION array, dimension (2)
           The original eigenvalues.  We assume D(1) < D(2).

    Z      (input) DOUBLE PRECISION array, dimension (2)
           The components of the updating vector.

    DELTA  (output) DOUBLE PRECISION array, dimension (2)
           The vector DELTA contains the information necessary
           to construct the eigenvectors.

    RHO    (input) DOUBLE PRECISION
           The scalar in the symmetric updating formula.

    DLAM   (output) DOUBLE PRECISION
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
	w = *rho * 2. * (z__[2] * z__[2] - z__[1] * z__[1]) / del + 1.;
	if (w > 0.) {
	    b = del + *rho * (z__[1] * z__[1] + z__[2] * z__[2]);
	    c__ = *rho * z__[1] * z__[1] * del;

/*           B > ZERO, always */

	    tau = c__ * 2. / (b + sqrt((d__1 = b * b - c__ * 4., abs(d__1))));
	    *dlam = d__[1] + tau;
	    delta[1] = -z__[1] / tau;
	    delta[2] = z__[2] / (del - tau);
	} else {
	    b = -del + *rho * (z__[1] * z__[1] + z__[2] * z__[2]);
	    c__ = *rho * z__[2] * z__[2] * del;
	    if (b > 0.) {
		tau = c__ * -2. / (b + sqrt(b * b + c__ * 4.));
	    } else {
		tau = (b - sqrt(b * b + c__ * 4.)) / 2.;
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
	if (b > 0.) {
	    tau = (b + sqrt(b * b + c__ * 4.)) / 2.;
	} else {
	    tau = c__ * 2. / (-b + sqrt(b * b + c__ * 4.));
	}
	*dlam = d__[2] + tau;
	delta[1] = -z__[1] / (del + tau);
	delta[2] = -z__[2] / tau;
	temp = sqrt(delta[1] * delta[1] + delta[2] * delta[2]);
	delta[1] /= temp;
	delta[2] /= temp;
    }
    return 0;

/*     End OF DLAED5 */

}