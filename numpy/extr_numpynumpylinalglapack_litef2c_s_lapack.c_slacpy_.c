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
typedef  int /*<<< orphan*/  real ;
typedef  void* logical ;
typedef  int integer ;

/* Variables and functions */
 int min (int,int) ; 

int slacpy_(char *uplo, integer *m, integer *n, real *a,
	integer *lda, real *b, integer *ldb)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2;

    /* Local variables */
    static integer i__, j;
    extern logical lsame_(char *, char *);


/*
    -- LAPACK auxiliary routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    SLACPY copies all or part of a two-dimensional matrix A to another
    matrix B.

    Arguments
    =========

    UPLO    (input) CHARACTER*1
            Specifies the part of the matrix A to be copied to B.
            = 'U':      Upper triangular part
            = 'L':      Lower triangular part
            Otherwise:  All of the matrix A

    M       (input) INTEGER
            The number of rows of the matrix A.  M >= 0.

    N       (input) INTEGER
            The number of columns of the matrix A.  N >= 0.

    A       (input) REAL array, dimension (LDA,N)
            The m by n matrix A.  If UPLO = 'U', only the upper triangle
            or trapezoid is accessed; if UPLO = 'L', only the lower
            triangle or trapezoid is accessed.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= max(1,M).

    B       (output) REAL array, dimension (LDB,N)
            On exit, B = A in the locations specified by UPLO.

    LDB     (input) INTEGER
            The leading dimension of the array B.  LDB >= max(1,M).

    =====================================================================
*/


    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    if (lsame_(uplo, "U")) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = min(j,*m);
	    for (i__ = 1; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = a[i__ + j * a_dim1];
/* L10: */
	    }
/* L20: */
	}
    } else if (lsame_(uplo, "L")) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = j; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = a[i__ + j * a_dim1];
/* L30: */
	    }
/* L40: */
	}
    } else {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = a[i__ + j * a_dim1];
/* L50: */
	    }
/* L60: */
	}
    }
    return 0;

/*     End of SLACPY */

}