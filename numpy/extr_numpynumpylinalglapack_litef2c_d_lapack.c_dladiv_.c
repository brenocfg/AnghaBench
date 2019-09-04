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
typedef  int doublereal ;

/* Variables and functions */
 scalar_t__ abs (int) ; 

int dladiv_(doublereal *a, doublereal *b, doublereal *c__,
	doublereal *d__, doublereal *p, doublereal *q)
{
    static doublereal e, f;


/*
    -- LAPACK auxiliary routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    DLADIV performs complex division in  real arithmetic

                          a + i*b
               p + i*q = ---------
                          c + i*d

    The algorithm is due to Robert L. Smith and can be found
    in D. Knuth, The art of Computer Programming, Vol.2, p.195

    Arguments
    =========

    A       (input) DOUBLE PRECISION
    B       (input) DOUBLE PRECISION
    C       (input) DOUBLE PRECISION
    D       (input) DOUBLE PRECISION
            The scalars a, b, c, and d in the above expression.

    P       (output) DOUBLE PRECISION
    Q       (output) DOUBLE PRECISION
            The scalars p and q in the above expression.

    =====================================================================
*/


    if (abs(*d__) < abs(*c__)) {
	e = *d__ / *c__;
	f = *c__ + *d__ * e;
	*p = (*a + *b * e) / f;
	*q = (*b - *a * e) / f;
    } else {
	e = *c__ / *d__;
	f = *d__ + *c__ * e;
	*p = (*b + *a * e) / f;
	*q = (-(*a) + *b * e) / f;
    }

    return 0;

/*     End of DLADIV */

}