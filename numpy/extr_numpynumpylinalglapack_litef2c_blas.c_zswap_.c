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
typedef  int integer ;
struct TYPE_4__ {int /*<<< orphan*/  i; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ doublecomplex ;

/* Variables and functions */

int zswap_(integer *n, doublecomplex *zx, integer *incx,
	doublecomplex *zy, integer *incy)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Local variables */
    static integer i__, ix, iy;
    static doublecomplex ztemp;


/*
    Purpose
    =======

       ZSWAP interchanges two vectors.

    Further Details
    ===============

       jack dongarra, 3/11/78.
       modified 12/3/93, array(1) declarations changed to array(*)

    =====================================================================
*/

    /* Parameter adjustments */
    --zy;
    --zx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*
         code for unequal increments or equal increments not equal
           to 1
*/

    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ix;
	ztemp.r = zx[i__2].r, ztemp.i = zx[i__2].i;
	i__2 = ix;
	i__3 = iy;
	zx[i__2].r = zy[i__3].r, zx[i__2].i = zy[i__3].i;
	i__2 = iy;
	zy[i__2].r = ztemp.r, zy[i__2].i = ztemp.i;
	ix += *incx;
	iy += *incy;
/* L10: */
    }
    return 0;

/*       code for both increments equal to 1 */
L20:
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	ztemp.r = zx[i__2].r, ztemp.i = zx[i__2].i;
	i__2 = i__;
	i__3 = i__;
	zx[i__2].r = zy[i__3].r, zx[i__2].i = zy[i__3].i;
	i__2 = i__;
	zy[i__2].r = ztemp.r, zy[i__2].i = ztemp.i;
/* L30: */
    }
    return 0;
}