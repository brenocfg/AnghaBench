#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int integer ;
typedef  void* doublereal ;
struct TYPE_3__ {int r; int i; } ;
typedef  TYPE_1__ doublecomplex ;

/* Variables and functions */

int zdscal_(integer *n, doublereal *da, doublecomplex *zx,
	integer *incx)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublecomplex z__1, z__2;

    /* Local variables */
    static integer i__, ix;


/*
    Purpose
    =======

       ZDSCAL scales a vector by a constant.

    Further Details
    ===============

       jack dongarra, 3/11/78.
       modified 3/93 to return if incx .le. 0.
       modified 12/3/93, array(1) declarations changed to array(*)

    =====================================================================
*/

    /* Parameter adjustments */
    --zx;

    /* Function Body */
    if (*n <= 0 || *incx <= 0) {
	return 0;
    }
    if (*incx == 1) {
	goto L20;
    }

/*        code for increment not equal to 1 */

    ix = 1;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ix;
	z__2.r = *da, z__2.i = 0.;
	i__3 = ix;
	z__1.r = z__2.r * zx[i__3].r - z__2.i * zx[i__3].i, z__1.i = z__2.r *
		zx[i__3].i + z__2.i * zx[i__3].r;
	zx[i__2].r = z__1.r, zx[i__2].i = z__1.i;
	ix += *incx;
/* L10: */
    }
    return 0;

/*        code for increment equal to 1 */

L20:
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	z__2.r = *da, z__2.i = 0.;
	i__3 = i__;
	z__1.r = z__2.r * zx[i__3].r - z__2.i * zx[i__3].i, z__1.i = z__2.r *
		zx[i__3].i + z__2.i * zx[i__3].r;
	zx[i__2].r = z__1.r, zx[i__2].i = z__1.i;
/* L30: */
    }
    return 0;
}