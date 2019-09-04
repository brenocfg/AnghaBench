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

int dlamc4_(integer *emin, doublereal *start, integer *base)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static doublereal a;
    static integer i__;
    static doublereal b1, b2, c1, c2, d1, d2, one, zero, rbase;
    extern doublereal dlamc3_(doublereal *, doublereal *);


/*
    -- LAPACK auxiliary routine (version 3.2) --
       Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..
       November 2006


    Purpose
    =======

    DLAMC4 is a service routine for DLAMC2.

    Arguments
    =========

    EMIN    (output) INTEGER
            The minimum exponent before (gradual) underflow, computed by
            setting A = START and dividing by BASE until the previous A
            can not be recovered.

    START   (input) DOUBLE PRECISION
            The starting point for determining EMIN.

    BASE    (input) INTEGER
            The base of the machine.

   =====================================================================
*/


    a = *start;
    one = 1.;
    rbase = one / *base;
    zero = 0.;
    *emin = 1;
    d__1 = a * rbase;
    b1 = dlamc3_(&d__1, &zero);
    c1 = a;
    c2 = a;
    d1 = a;
    d2 = a;
/*
   +    WHILE( ( C1.EQ.A ).AND.( C2.EQ.A ).AND.
      $       ( D1.EQ.A ).AND.( D2.EQ.A )      )LOOP
*/
L10:
    if (c1 == a && c2 == a && d1 == a && d2 == a) {
	--(*emin);
	a = b1;
	d__1 = a / *base;
	b1 = dlamc3_(&d__1, &zero);
	d__1 = b1 * *base;
	c1 = dlamc3_(&d__1, &zero);
	d1 = zero;
	i__1 = *base;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d1 += b1;
/* L20: */
	}
	d__1 = a * rbase;
	b2 = dlamc3_(&d__1, &zero);
	d__1 = b2 / rbase;
	c2 = dlamc3_(&d__1, &zero);
	d2 = zero;
	i__1 = *base;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d2 += b2;
/* L30: */
	}
	goto L10;
    }
/* +    END WHILE */

    return 0;

/*     End of DLAMC4 */

}