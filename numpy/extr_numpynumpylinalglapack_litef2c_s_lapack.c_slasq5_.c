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
typedef  scalar_t__ logical ;
typedef  int integer ;

/* Variables and functions */
 float dmin (float,float) ; 

int slasq5_(integer *i0, integer *n0, real *z__, integer *pp,
	 real *tau, real *dmin__, real *dmin1, real *dmin2, real *dn, real *
	dnm1, real *dnm2, logical *ieee)
{
    /* System generated locals */
    integer i__1;
    real r__1, r__2;

    /* Local variables */
    static real d__;
    static integer j4, j4p2;
    static real emin, temp;


/*
    -- LAPACK routine (version 3.2)                                    --

    -- Contributed by Osni Marques of the Lawrence Berkeley National   --
    -- Laboratory and Beresford Parlett of the Univ. of California at  --
    -- Berkeley                                                        --
    -- November 2008                                                   --

    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--


    Purpose
    =======

    SLASQ5 computes one dqds transform in ping-pong form, one
    version for IEEE machines another for non IEEE machines.

    Arguments
    =========

    I0    (input) INTEGER
          First index.

    N0    (input) INTEGER
          Last index.

    Z     (input) REAL array, dimension ( 4*N )
          Z holds the qd array. EMIN is stored in Z(4*N0) to avoid
          an extra argument.

    PP    (input) INTEGER
          PP=0 for ping, PP=1 for pong.

    TAU   (input) REAL
          This is the shift.

    DMIN  (output) REAL
          Minimum value of d.

    DMIN1 (output) REAL
          Minimum value of d, excluding D( N0 ).

    DMIN2 (output) REAL
          Minimum value of d, excluding D( N0 ) and D( N0-1 ).

    DN    (output) REAL
          d(N0), the last value of d.

    DNM1  (output) REAL
          d(N0-1).

    DNM2  (output) REAL
          d(N0-2).

    IEEE  (input) LOGICAL
          Flag for IEEE or non IEEE arithmetic.

    =====================================================================
*/


    /* Parameter adjustments */
    --z__;

    /* Function Body */
    if (*n0 - *i0 - 1 <= 0) {
	return 0;
    }

    j4 = (*i0 << 2) + *pp - 3;
    emin = z__[j4 + 4];
    d__ = z__[j4] - *tau;
    *dmin__ = d__;
    *dmin1 = -z__[j4];

    if (*ieee) {

/*        Code for IEEE arithmetic. */

	if (*pp == 0) {
	    i__1 = *n0 - 3 << 2;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		z__[j4 - 2] = d__ + z__[j4 - 1];
		temp = z__[j4 + 1] / z__[j4 - 2];
		d__ = d__ * temp - *tau;
		*dmin__ = dmin(*dmin__,d__);
		z__[j4] = z__[j4 - 1] * temp;
/* Computing MIN */
		r__1 = z__[j4];
		emin = dmin(r__1,emin);
/* L10: */
	    }
	} else {
	    i__1 = *n0 - 3 << 2;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		z__[j4 - 3] = d__ + z__[j4];
		temp = z__[j4 + 2] / z__[j4 - 3];
		d__ = d__ * temp - *tau;
		*dmin__ = dmin(*dmin__,d__);
		z__[j4 - 1] = z__[j4] * temp;
/* Computing MIN */
		r__1 = z__[j4 - 1];
		emin = dmin(r__1,emin);
/* L20: */
	    }
	}

/*        Unroll last two steps. */

	*dnm2 = d__;
	*dmin2 = *dmin__;
	j4 = (*n0 - 2 << 2) - *pp;
	j4p2 = j4 + (*pp << 1) - 1;
	z__[j4 - 2] = *dnm2 + z__[j4p2];
	z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	*dnm1 = z__[j4p2 + 2] * (*dnm2 / z__[j4 - 2]) - *tau;
	*dmin__ = dmin(*dmin__,*dnm1);

	*dmin1 = *dmin__;
	j4 += 4;
	j4p2 = j4 + (*pp << 1) - 1;
	z__[j4 - 2] = *dnm1 + z__[j4p2];
	z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	*dn = z__[j4p2 + 2] * (*dnm1 / z__[j4 - 2]) - *tau;
	*dmin__ = dmin(*dmin__,*dn);

    } else {

/*        Code for non IEEE arithmetic. */

	if (*pp == 0) {
	    i__1 = *n0 - 3 << 2;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		z__[j4 - 2] = d__ + z__[j4 - 1];
		if (d__ < 0.f) {
		    return 0;
		} else {
		    z__[j4] = z__[j4 + 1] * (z__[j4 - 1] / z__[j4 - 2]);
		    d__ = z__[j4 + 1] * (d__ / z__[j4 - 2]) - *tau;
		}
		*dmin__ = dmin(*dmin__,d__);
/* Computing MIN */
		r__1 = emin, r__2 = z__[j4];
		emin = dmin(r__1,r__2);
/* L30: */
	    }
	} else {
	    i__1 = *n0 - 3 << 2;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		z__[j4 - 3] = d__ + z__[j4];
		if (d__ < 0.f) {
		    return 0;
		} else {
		    z__[j4 - 1] = z__[j4 + 2] * (z__[j4] / z__[j4 - 3]);
		    d__ = z__[j4 + 2] * (d__ / z__[j4 - 3]) - *tau;
		}
		*dmin__ = dmin(*dmin__,d__);
/* Computing MIN */
		r__1 = emin, r__2 = z__[j4 - 1];
		emin = dmin(r__1,r__2);
/* L40: */
	    }
	}

/*        Unroll last two steps. */

	*dnm2 = d__;
	*dmin2 = *dmin__;
	j4 = (*n0 - 2 << 2) - *pp;
	j4p2 = j4 + (*pp << 1) - 1;
	z__[j4 - 2] = *dnm2 + z__[j4p2];
	if (*dnm2 < 0.f) {
	    return 0;
	} else {
	    z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	    *dnm1 = z__[j4p2 + 2] * (*dnm2 / z__[j4 - 2]) - *tau;
	}
	*dmin__ = dmin(*dmin__,*dnm1);

	*dmin1 = *dmin__;
	j4 += 4;
	j4p2 = j4 + (*pp << 1) - 1;
	z__[j4 - 2] = *dnm1 + z__[j4p2];
	if (*dnm1 < 0.f) {
	    return 0;
	} else {
	    z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	    *dn = z__[j4p2 + 2] * (*dnm1 / z__[j4 - 2]) - *tau;
	}
	*dmin__ = dmin(*dmin__,*dn);

    }

    z__[j4 + 2] = *dn;
    z__[(*n0 << 2) - *pp] = emin;
    return 0;

/*     End of SLASQ5 */

}