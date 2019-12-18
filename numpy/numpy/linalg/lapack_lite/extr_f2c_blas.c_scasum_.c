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
typedef  float real ;
typedef  int integer ;
typedef  float doublereal ;
struct TYPE_4__ {float r; } ;
typedef  TYPE_1__ complex ;

/* Variables and functions */
 int /*<<< orphan*/  dabs (float) ; 
 float r_imag (TYPE_1__*) ; 

doublereal scasum_(integer *n, complex *cx, integer *incx)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    real ret_val, r__1, r__2;

    /* Local variables */
    static integer i__, nincx;
    static real stemp;


/*
    Purpose
    =======

       SCASUM takes the sum of the absolute values of a complex vector and
       returns a single precision result.

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
    ret_val = 0.f;
    stemp = 0.f;
    if (*n <= 0 || *incx <= 0) {
	return ret_val;
    }
    if (*incx == 1) {
	goto L20;
    }

/*        code for increment not equal to 1 */

    nincx = *n * *incx;
    i__1 = nincx;
    i__2 = *incx;
    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	i__3 = i__;
	stemp = stemp + (r__1 = cx[i__3].r, dabs(r__1)) + (r__2 = r_imag(&cx[
		i__]), dabs(r__2));
/* L10: */
    }
    ret_val = stemp;
    return ret_val;

/*        code for increment equal to 1 */

L20:
    i__2 = *n;
    for (i__ = 1; i__ <= i__2; ++i__) {
	i__1 = i__;
	stemp = stemp + (r__1 = cx[i__1].r, dabs(r__1)) + (r__2 = r_imag(&cx[
		i__]), dabs(r__2));
/* L30: */
    }
    ret_val = stemp;
    return ret_val;
}