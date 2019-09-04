#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  float real ;
typedef  void* logical ;
typedef  int integer ;
struct TYPE_5__ {float r; float i; } ;
typedef  TYPE_1__ complex ;
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int c__1 ; 
 TYPE_1__ c_b57 ; 
 int /*<<< orphan*/  csscal_ (int*,float*,TYPE_1__*,int*) ; 
 int max (int,int) ; 
 float sqrt (float) ; 
 int /*<<< orphan*/  xerbla_ (char*,int*) ; 

int cpotf2_(char *uplo, integer *n, complex *a, integer *lda,
	 integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    real r__1;
    complex q__1, q__2;

    /* Local variables */
    static integer j;
    static real ajj;
    extern /* Complex */ VOID cdotc_(complex *, integer *, complex *, integer
	    *, complex *, integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int cgemv_(char *, integer *, integer *, complex *
	    , complex *, integer *, complex *, integer *, complex *, complex *
	    , integer *);
    static logical upper;
    extern /* Subroutine */ int clacgv_(integer *, complex *, integer *),
	    csscal_(integer *, real *, complex *, integer *), xerbla_(char *,
	    integer *);
    extern logical sisnan_(real *);


/*
    -- LAPACK routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    CPOTF2 computes the Cholesky factorization of a complex Hermitian
    positive definite matrix A.

    The factorization has the form
       A = U' * U ,  if UPLO = 'U', or
       A = L  * L',  if UPLO = 'L',
    where U is an upper triangular matrix and L is lower triangular.

    This is the unblocked version of the algorithm, calling Level 2 BLAS.

    Arguments
    =========

    UPLO    (input) CHARACTER*1
            Specifies whether the upper or lower triangular part of the
            Hermitian matrix A is stored.
            = 'U':  Upper triangular
            = 'L':  Lower triangular

    N       (input) INTEGER
            The order of the matrix A.  N >= 0.

    A       (input/output) COMPLEX array, dimension (LDA,N)
            On entry, the Hermitian matrix A.  If UPLO = 'U', the leading
            n by n upper triangular part of A contains the upper
            triangular part of the matrix A, and the strictly lower
            triangular part of A is not referenced.  If UPLO = 'L', the
            leading n by n lower triangular part of A contains the lower
            triangular part of the matrix A, and the strictly upper
            triangular part of A is not referenced.

            On exit, if INFO = 0, the factor U or L from the Cholesky
            factorization A = U'*U  or A = L*L'.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= max(1,N).

    INFO    (output) INTEGER
            = 0: successful exit
            < 0: if INFO = -k, the k-th argument had an illegal value
            > 0: if INFO = k, the leading minor of order k is not
                 positive definite, and the factorization could not be
                 completed.

    =====================================================================


       Test the input parameters.
*/

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U");
    if (! upper && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*n)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CPOTF2", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

    if (upper) {

/*        Compute the Cholesky factorization A = U'*U. */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {

/*           Compute U(J,J) and test for non-positive-definiteness. */

	    i__2 = j + j * a_dim1;
	    r__1 = a[i__2].r;
	    i__3 = j - 1;
	    cdotc_(&q__2, &i__3, &a[j * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1]
		    , &c__1);
	    q__1.r = r__1 - q__2.r, q__1.i = -q__2.i;
	    ajj = q__1.r;
	    if (ajj <= 0.f || sisnan_(&ajj)) {
		i__2 = j + j * a_dim1;
		a[i__2].r = ajj, a[i__2].i = 0.f;
		goto L30;
	    }
	    ajj = sqrt(ajj);
	    i__2 = j + j * a_dim1;
	    a[i__2].r = ajj, a[i__2].i = 0.f;

/*           Compute elements J+1:N of row J. */

	    if (j < *n) {
		i__2 = j - 1;
		clacgv_(&i__2, &a[j * a_dim1 + 1], &c__1);
		i__2 = j - 1;
		i__3 = *n - j;
		q__1.r = -1.f, q__1.i = -0.f;
		cgemv_("Transpose", &i__2, &i__3, &q__1, &a[(j + 1) * a_dim1
			+ 1], lda, &a[j * a_dim1 + 1], &c__1, &c_b57, &a[j + (
			j + 1) * a_dim1], lda);
		i__2 = j - 1;
		clacgv_(&i__2, &a[j * a_dim1 + 1], &c__1);
		i__2 = *n - j;
		r__1 = 1.f / ajj;
		csscal_(&i__2, &r__1, &a[j + (j + 1) * a_dim1], lda);
	    }
/* L10: */
	}
    } else {

/*        Compute the Cholesky factorization A = L*L'. */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {

/*           Compute L(J,J) and test for non-positive-definiteness. */

	    i__2 = j + j * a_dim1;
	    r__1 = a[i__2].r;
	    i__3 = j - 1;
	    cdotc_(&q__2, &i__3, &a[j + a_dim1], lda, &a[j + a_dim1], lda);
	    q__1.r = r__1 - q__2.r, q__1.i = -q__2.i;
	    ajj = q__1.r;
	    if (ajj <= 0.f || sisnan_(&ajj)) {
		i__2 = j + j * a_dim1;
		a[i__2].r = ajj, a[i__2].i = 0.f;
		goto L30;
	    }
	    ajj = sqrt(ajj);
	    i__2 = j + j * a_dim1;
	    a[i__2].r = ajj, a[i__2].i = 0.f;

/*           Compute elements J+1:N of column J. */

	    if (j < *n) {
		i__2 = j - 1;
		clacgv_(&i__2, &a[j + a_dim1], lda);
		i__2 = *n - j;
		i__3 = j - 1;
		q__1.r = -1.f, q__1.i = -0.f;
		cgemv_("No transpose", &i__2, &i__3, &q__1, &a[j + 1 + a_dim1]
			, lda, &a[j + a_dim1], lda, &c_b57, &a[j + 1 + j *
			a_dim1], &c__1);
		i__2 = j - 1;
		clacgv_(&i__2, &a[j + a_dim1], lda);
		i__2 = *n - j;
		r__1 = 1.f / ajj;
		csscal_(&i__2, &r__1, &a[j + 1 + j * a_dim1], &c__1);
	    }
/* L20: */
	}
    }
    goto L40;

L30:
    *info = j;

L40:
    return 0;

/*     End of CPOTF2 */

}