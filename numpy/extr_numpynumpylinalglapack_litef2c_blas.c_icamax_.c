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
typedef  scalar_t__ real ;
typedef  int integer ;
typedef  void* doublereal ;
typedef  int /*<<< orphan*/  complex ;

/* Variables and functions */

integer icamax_(integer *n, complex *cx, integer *incx)
{
    /* System generated locals */
    integer ret_val, i__1;

    /* Local variables */
    static integer i__, ix;
    static real smax;
    extern doublereal scabs1_(complex *);


/*
    Purpose
    =======

       ICAMAX finds the index of element having max. absolute value.

    Further Details
    ===============

       jack dongarra, linpack, 3/11/78.
       modified 3/93 to return if incx .le. 0.
       modified 12/3/93, array(1) declarations changed to array(*)

    =====================================================================
*/

    /* Parameter adjustments */
    --cx;

    /* Function Body */
    ret_val = 0;
    if (*n < 1 || *incx <= 0) {
	return ret_val;
    }
    ret_val = 1;
    if (*n == 1) {
	return ret_val;
    }
    if (*incx == 1) {
	goto L20;
    }

/*        code for increment not equal to 1 */

    ix = 1;
    smax = scabs1_(&cx[1]);
    ix += *incx;
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if (scabs1_(&cx[ix]) <= smax) {
	    goto L5;
	}
	ret_val = i__;
	smax = scabs1_(&cx[ix]);
L5:
	ix += *incx;
/* L10: */
    }
    return ret_val;

/*        code for increment equal to 1 */

L20:
    smax = scabs1_(&cx[1]);
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if (scabs1_(&cx[i__]) <= smax) {
	    goto L30;
	}
	ret_val = i__;
	smax = scabs1_(&cx[i__]);
L30:
	;
    }
    return ret_val;
}