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
typedef  int real ;

/* Variables and functions */
 scalar_t__ dabs (int) ; 

int sladiv_(real *a, real *b, real *c__, real *d__, real *p,
	real *q)
{
    static real e, f;


/*
    -- LAPACK auxiliary routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    SLADIV performs complex division in  real arithmetic

                          a + i*b
               p + i*q = ---------
                          c + i*d

    The algorithm is due to Robert L. Smith and can be found
    in D. Knuth, The art of Computer Programming, Vol.2, p.195

    Arguments
    =========

    A       (input) REAL
    B       (input) REAL
    C       (input) REAL
    D       (input) REAL
            The scalars a, b, c, and d in the above expression.

    P       (output) REAL
    Q       (output) REAL
            The scalars p and q in the above expression.

    =====================================================================
*/


    if (dabs(*d__) < dabs(*c__)) {
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

/*     End of SLADIV */

}