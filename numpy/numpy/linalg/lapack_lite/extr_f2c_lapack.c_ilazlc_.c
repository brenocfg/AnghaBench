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
struct TYPE_3__ {int r; int i; } ;
typedef  TYPE_1__ doublecomplex ;

/* Variables and functions */

integer ilazlc_(integer *m, integer *n, doublecomplex *a, integer *lda)
{
    /* System generated locals */
    integer a_dim1, a_offset, ret_val, i__1, i__2;

    /* Local variables */
    static integer i__;


/*
    -- LAPACK auxiliary routine (version 3.2.2)                        --

    -- June 2010                                                       --

    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--


    Purpose
    =======

    ILAZLC scans A for its last non-zero column.

    Arguments
    =========

    M       (input) INTEGER
            The number of rows of the matrix A.

    N       (input) INTEGER
            The number of columns of the matrix A.

    A       (input) COMPLEX*16 array, dimension (LDA,N)
            The m by n matrix A.

    LDA     (input) INTEGER
            The leading dimension of the array A. LDA >= max(1,M).

    =====================================================================


       Quick test for the common case where one corner is non-zero.
*/
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    if (*n == 0) {
	ret_val = *n;
    } else /* if(complicated condition) */ {
	i__1 = *n * a_dim1 + 1;
	i__2 = *m + *n * a_dim1;
	if (a[i__1].r != 0. || a[i__1].i != 0. || (a[i__2].r != 0. || a[i__2]
		.i != 0.)) {
	    ret_val = *n;
	} else {
/*     Now scan each column from the end, returning with the first non-zero. */
	    for (ret_val = *n; ret_val >= 1; --ret_val) {
		i__1 = *m;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    i__2 = i__ + ret_val * a_dim1;
		    if (a[i__2].r != 0. || a[i__2].i != 0.) {
			return ret_val;
		    }
		}
	    }
	}
    }
    return ret_val;
}