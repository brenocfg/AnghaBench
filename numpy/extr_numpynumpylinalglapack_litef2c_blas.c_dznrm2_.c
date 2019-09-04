#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int integer ;
typedef  int doublereal ;
struct TYPE_4__ {int r; } ;
typedef  TYPE_1__ doublecomplex ;

/* Variables and functions */
 int /*<<< orphan*/  abs (int) ; 
 int d_imag (TYPE_1__*) ; 
 int sqrt (int) ; 

doublereal dznrm2_(integer *n, doublecomplex *x, integer *incx)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal ret_val, d__1;

    /* Local variables */
    static integer ix;
    static doublereal ssq, temp, norm, scale;


/*
    Purpose
    =======

    DZNRM2 returns the euclidean norm of a vector via the function
    name, so that

       DZNRM2 := sqrt( conjg( x' )*x )

    Further Details
    ===============

    -- This version written on 25-October-1982.
       Modified on 14-October-1993 to inline the call to ZLASSQ.
       Sven Hammarling, Nag Ltd.

    =====================================================================
*/

    /* Parameter adjustments */
    --x;

    /* Function Body */
    if (*n < 1 || *incx < 1) {
	norm = 0.;
    } else {
	scale = 0.;
	ssq = 1.;
/*
          The following loop is equivalent to this call to the LAPACK
          auxiliary routine:
          CALL ZLASSQ( N, X, INCX, SCALE, SSQ )
*/

	i__1 = (*n - 1) * *incx + 1;
	i__2 = *incx;
	for (ix = 1; i__2 < 0 ? ix >= i__1 : ix <= i__1; ix += i__2) {
	    i__3 = ix;
	    if (x[i__3].r != 0.) {
		i__3 = ix;
		temp = (d__1 = x[i__3].r, abs(d__1));
		if (scale < temp) {
/* Computing 2nd power */
		    d__1 = scale / temp;
		    ssq = ssq * (d__1 * d__1) + 1.;
		    scale = temp;
		} else {
/* Computing 2nd power */
		    d__1 = temp / scale;
		    ssq += d__1 * d__1;
		}
	    }
	    if (d_imag(&x[ix]) != 0.) {
		temp = (d__1 = d_imag(&x[ix]), abs(d__1));
		if (scale < temp) {
/* Computing 2nd power */
		    d__1 = scale / temp;
		    ssq = ssq * (d__1 * d__1) + 1.;
		    scale = temp;
		} else {
/* Computing 2nd power */
		    d__1 = temp / scale;
		    ssq += d__1 * d__1;
		}
	    }
/* L10: */
	}
	norm = scale * sqrt(ssq);
    }

    ret_val = norm;
    return ret_val;

/*     End of DZNRM2. */

}