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

/* Variables and functions */
 float dabs (float) ; 
 float sqrt (float) ; 

int slae2_(real *a, real *b, real *c__, real *rt1, real *rt2)
{
    /* System generated locals */
    real r__1;

    /* Local variables */
    static real ab, df, tb, sm, rt, adf, acmn, acmx;


/*
    -- LAPACK auxiliary routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    SLAE2  computes the eigenvalues of a 2-by-2 symmetric matrix
       [  A   B  ]
       [  B   C  ].
    On return, RT1 is the eigenvalue of larger absolute value, and RT2
    is the eigenvalue of smaller absolute value.

    Arguments
    =========

    A       (input) REAL
            The (1,1) element of the 2-by-2 matrix.

    B       (input) REAL
            The (1,2) and (2,1) elements of the 2-by-2 matrix.

    C       (input) REAL
            The (2,2) element of the 2-by-2 matrix.

    RT1     (output) REAL
            The eigenvalue of larger absolute value.

    RT2     (output) REAL
            The eigenvalue of smaller absolute value.

    Further Details
    ===============

    RT1 is accurate to a few ulps barring over/underflow.

    RT2 may be inaccurate if there is massive cancellation in the
    determinant A*C-B*B; higher precision or correctly rounded or
    correctly truncated arithmetic would be needed to compute RT2
    accurately in all cases.

    Overflow is possible only if RT1 is within a factor of 5 of overflow.
    Underflow is harmless if the input data is 0 or exceeds
       underflow_threshold / macheps.

   =====================================================================


       Compute the eigenvalues
*/

    sm = *a + *c__;
    df = *a - *c__;
    adf = dabs(df);
    tb = *b + *b;
    ab = dabs(tb);
    if (dabs(*a) > dabs(*c__)) {
	acmx = *a;
	acmn = *c__;
    } else {
	acmx = *c__;
	acmn = *a;
    }
    if (adf > ab) {
/* Computing 2nd power */
	r__1 = ab / adf;
	rt = adf * sqrt(r__1 * r__1 + 1.f);
    } else if (adf < ab) {
/* Computing 2nd power */
	r__1 = adf / ab;
	rt = ab * sqrt(r__1 * r__1 + 1.f);
    } else {

/*        Includes case AB=ADF=0 */

	rt = ab * sqrt(2.f);
    }
    if (sm < 0.f) {
	*rt1 = (sm - rt) * .5f;

/*
          Order of execution important.
          To get fully accurate smaller eigenvalue,
          next line needs to be executed in higher precision.
*/

	*rt2 = acmx / *rt1 * acmn - *b / *rt1 * *b;
    } else if (sm > 0.f) {
	*rt1 = (sm + rt) * .5f;

/*
          Order of execution important.
          To get fully accurate smaller eigenvalue,
          next line needs to be executed in higher precision.
*/

	*rt2 = acmx / *rt1 * acmn - *b / *rt1 * *b;
    } else {

/*        Includes case RT1 = RT2 = 0 */

	*rt1 = rt * .5f;
	*rt2 = rt * -.5f;
    }
    return 0;

/*     End of SLAE2 */

}