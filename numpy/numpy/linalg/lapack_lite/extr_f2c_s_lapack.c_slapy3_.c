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
typedef  float doublereal ;

/* Variables and functions */
 float dabs (float) ; 
 float dmax (float,float) ; 
 float max (float,float) ; 
 float sqrt (float) ; 

doublereal slapy3_(real *x, real *y, real *z__)
{
    /* System generated locals */
    real ret_val, r__1, r__2, r__3;

    /* Local variables */
    static real w, xabs, yabs, zabs;


/*
    -- LAPACK auxiliary routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    SLAPY3 returns sqrt(x**2+y**2+z**2), taking care not to cause
    unnecessary overflow.

    Arguments
    =========

    X       (input) REAL
    Y       (input) REAL
    Z       (input) REAL
            X, Y and Z specify the values x, y and z.

    =====================================================================
*/


    xabs = dabs(*x);
    yabs = dabs(*y);
    zabs = dabs(*z__);
/* Computing MAX */
    r__1 = max(xabs,yabs);
    w = dmax(r__1,zabs);
    if (w == 0.f) {
/*
       W can be zero for max(0,nan,0)
       adding all three entries together will make sure
       NaN will not disappear.
*/
	ret_val = xabs + yabs + zabs;
    } else {
/* Computing 2nd power */
	r__1 = xabs / w;
/* Computing 2nd power */
	r__2 = yabs / w;
/* Computing 2nd power */
	r__3 = zabs / w;
	ret_val = w * sqrt(r__1 * r__1 + r__2 * r__2 + r__3 * r__3);
    }
    return ret_val;

/*     End of SLAPY3 */

}