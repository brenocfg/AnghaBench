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
typedef  void* logical ;
typedef  scalar_t__ integer ;
typedef  int /*<<< orphan*/  complex ;

/* Variables and functions */
 int /*<<< orphan*/  clauum_ (char*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ctrtri_ (char*,char*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ max (int,scalar_t__) ; 

int cpotri_(char *uplo, integer *n, complex *a, integer *lda,
	 integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1;

    /* Local variables */
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int xerbla_(char *, integer *), clauum_(
	    char *, integer *, complex *, integer *, integer *),
	    ctrtri_(char *, char *, integer *, complex *, integer *, integer *
	    );


/*
    -- LAPACK routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    CPOTRI computes the inverse of a complex Hermitian positive definite
    matrix A using the Cholesky factorization A = U**H*U or A = L*L**H
    computed by CPOTRF.

    Arguments
    =========

    UPLO    (input) CHARACTER*1
            = 'U':  Upper triangle of A is stored;
            = 'L':  Lower triangle of A is stored.

    N       (input) INTEGER
            The order of the matrix A.  N >= 0.

    A       (input/output) COMPLEX array, dimension (LDA,N)
            On entry, the triangular factor U or L from the Cholesky
            factorization A = U**H*U or A = L*L**H, as computed by
            CPOTRF.
            On exit, the upper or lower triangle of the (Hermitian)
            inverse of A, overwriting the input factor U or L.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= max(1,N).

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value
            > 0:  if INFO = i, the (i,i) element of the factor U or L is
                  zero, and the inverse could not be computed.

    =====================================================================


       Test the input parameters.
*/

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *info = 0;
    if (! lsame_(uplo, "U") && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*n)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CPOTRI", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Invert the triangular Cholesky factor U or L. */

    ctrtri_(uplo, "Non-unit", n, &a[a_offset], lda, info);
    if (*info > 0) {
	return 0;
    }

/*     Form inv(U)*inv(U)' or inv(L)'*inv(L). */

    clauum_(uplo, n, &a[a_offset], lda, info);

    return 0;

/*     End of CPOTRI */

}