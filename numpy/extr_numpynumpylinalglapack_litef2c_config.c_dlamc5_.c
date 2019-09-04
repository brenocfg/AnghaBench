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
typedef  scalar_t__ logical ;
typedef  int integer ;
typedef  int doublereal ;

/* Variables and functions */
 int c_b32 ; 

int dlamc5_(integer *beta, integer *p, integer *emin,
	logical *ieee, integer *emax, doublereal *rmax)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static integer i__;
    static doublereal y, z__;
    static integer try__, lexp;
    static doublereal oldy;
    static integer uexp, nbits;
    extern doublereal dlamc3_(doublereal *, doublereal *);
    static doublereal recbas;
    static integer exbits, expsum;


/*
    -- LAPACK auxiliary routine (version 3.2) --
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..
       November 2006


    Purpose
    =======

    DLAMC5 attempts to compute RMAX, the largest machine floating-point
    number, without overflow.  It assumes that EMAX + abs(EMIN) sum
    approximately to a power of 2.  It will fail on machines where this
    assumption does not hold, for example, the Cyber 205 (EMIN = -28625,
    EMAX = 28718).  It will also fail if the value supplied for EMIN is
    too large (i.e. too close to zero), probably with overflow.

    Arguments
    =========

    BETA    (input) INTEGER
            The base of floating-point arithmetic.

    P       (input) INTEGER
            The number of base BETA digits in the mantissa of a
            floating-point value.

    EMIN    (input) INTEGER
            The minimum exponent before (gradual) underflow.

    IEEE    (input) LOGICAL
            A logical flag specifying whether or not the arithmetic
            system is thought to comply with the IEEE standard.

    EMAX    (output) INTEGER
            The largest exponent before overflow

    RMAX    (output) DOUBLE PRECISION
            The largest machine floating-point number.

   =====================================================================


       First compute LEXP and UEXP, two powers of 2 that bound
       abs(EMIN). We then assume that EMAX + abs(EMIN) will sum
       approximately to the bound that is closest to abs(EMIN).
       (EMAX is the exponent of the required number RMAX).
*/

    lexp = 1;
    exbits = 1;
L10:
    try__ = lexp << 1;
    if (try__ <= -(*emin)) {
	lexp = try__;
	++exbits;
	goto L10;
    }
    if (lexp == -(*emin)) {
	uexp = lexp;
    } else {
	uexp = try__;
	++exbits;
    }

/*
       Now -LEXP is less than or equal to EMIN, and -UEXP is greater
       than or equal to EMIN. EXBITS is the number of bits needed to
       store the exponent.
*/

    if (uexp + *emin > -lexp - *emin) {
	expsum = lexp << 1;
    } else {
	expsum = uexp << 1;
    }

/*
       EXPSUM is the exponent range, approximately equal to
       EMAX - EMIN + 1 .
*/

    *emax = expsum + *emin - 1;
    nbits = exbits + 1 + *p;

/*
       NBITS is the total number of bits needed to store a
       floating-point number.
*/

    if (nbits % 2 == 1 && *beta == 2) {

/*
          Either there are an odd number of bits used to store a
          floating-point number, which is unlikely, or some bits are
          not used in the representation of numbers, which is possible,
          (e.g. Cray machines) or the mantissa has an implicit bit,
          (e.g. IEEE machines, Dec Vax machines), which is perhaps the
          most likely. We have to assume the last alternative.
          If this is true, then we need to reduce EMAX by one because
          there must be some way of representing zero in an implicit-bit
          system. On machines like Cray, we are reducing EMAX by one
          unnecessarily.
*/

	--(*emax);
    }

    if (*ieee) {

/*
          Assume we are on an IEEE machine which reserves one exponent
          for infinity and NaN.
*/

	--(*emax);
    }

/*
       Now create RMAX, the largest machine number, which should
       be equal to (1.0 - BETA**(-P)) * BETA**EMAX .

       First compute 1.0 - BETA**(-P), being careful that the
       result is less than 1.0 .
*/

    recbas = 1. / *beta;
    z__ = *beta - 1.;
    y = 0.;
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	z__ *= recbas;
	if (y < 1.) {
	    oldy = y;
	}
	y = dlamc3_(&y, &z__);
/* L20: */
    }
    if (y >= 1.) {
	y = oldy;
    }

/*     Now multiply by BETA**EMAX to get RMAX. */

    i__1 = *emax;
    for (i__ = 1; i__ <= i__1; ++i__) {
	d__1 = y * *beta;
	y = dlamc3_(&d__1, &c_b32);
/* L30: */
    }

    *rmax = y;
    return 0;

/*     End of DLAMC5 */

}