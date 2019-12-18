#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int integer ;
typedef  scalar_t__ doublereal ;
struct TYPE_14__ {int r; int i; } ;
typedef  TYPE_1__ doublecomplex ;

/* Variables and functions */
 scalar_t__ SAFEMINIMUM ; 
 int c__1 ; 
 TYPE_1__ c_b57 ; 
 int max (int,int) ; 
 int min (int,int) ; 
 scalar_t__ z_abs (TYPE_1__*) ; 
 int /*<<< orphan*/  z_div (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zgeru_ (int*,int*,TYPE_1__*,TYPE_1__*,int*,TYPE_1__*,int*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  zswap_ (int*,TYPE_1__*,int*,TYPE_1__*,int*) ; 

int zgetf2_(integer *m, integer *n, doublecomplex *a,
	integer *lda, integer *ipiv, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublecomplex z__1;

    /* Local variables */
    static integer i__, j, jp;
    static doublereal sfmin;
    extern /* Subroutine */ int zscal_(integer *, doublecomplex *,
	    doublecomplex *, integer *), zgeru_(integer *, integer *,
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *,
	    integer *, doublecomplex *, integer *), zswap_(integer *,
	    doublecomplex *, integer *, doublecomplex *, integer *);

    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer izamax_(integer *, doublecomplex *, integer *);


/*
    -- LAPACK routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    ZGETF2 computes an LU factorization of a general m-by-n matrix A
    using partial pivoting with row interchanges.

    The factorization has the form
       A = P * L * U
    where P is a permutation matrix, L is lower triangular with unit
    diagonal elements (lower trapezoidal if m > n), and U is upper
    triangular (upper trapezoidal if m < n).

    This is the right-looking Level 2 BLAS version of the algorithm.

    Arguments
    =========

    M       (input) INTEGER
            The number of rows of the matrix A.  M >= 0.

    N       (input) INTEGER
            The number of columns of the matrix A.  N >= 0.

    A       (input/output) COMPLEX*16 array, dimension (LDA,N)
            On entry, the m by n matrix to be factored.
            On exit, the factors L and U from the factorization
            A = P*L*U; the unit diagonal elements of L are not stored.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= max(1,M).

    IPIV    (output) INTEGER array, dimension (min(M,N))
            The pivot indices; for 1 <= i <= min(M,N), row i of the
            matrix was interchanged with row IPIV(i).

    INFO    (output) INTEGER
            = 0: successful exit
            < 0: if INFO = -k, the k-th argument had an illegal value
            > 0: if INFO = k, U(k,k) is exactly zero. The factorization
                 has been completed, but the factor U is exactly
                 singular, and division by zero will occur if it is used
                 to solve a system of equations.

    =====================================================================


       Test the input parameters.
*/

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("ZGETF2", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Compute machine safe minimum */

    sfmin = SAFEMINIMUM;

    i__1 = min(*m,*n);
    for (j = 1; j <= i__1; ++j) {

/*        Find pivot and test for singularity. */

	i__2 = *m - j + 1;
	jp = j - 1 + izamax_(&i__2, &a[j + j * a_dim1], &c__1);
	ipiv[j] = jp;
	i__2 = jp + j * a_dim1;
	if (a[i__2].r != 0. || a[i__2].i != 0.) {

/*           Apply the interchange to columns 1:N. */

	    if (jp != j) {
		zswap_(n, &a[j + a_dim1], lda, &a[jp + a_dim1], lda);
	    }

/*           Compute elements J+1:M of J-th column. */

	    if (j < *m) {
		if (z_abs(&a[j + j * a_dim1]) >= sfmin) {
		    i__2 = *m - j;
		    z_div(&z__1, &c_b57, &a[j + j * a_dim1]);
		    zscal_(&i__2, &z__1, &a[j + 1 + j * a_dim1], &c__1);
		} else {
		    i__2 = *m - j;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			i__3 = j + i__ + j * a_dim1;
			z_div(&z__1, &a[j + i__ + j * a_dim1], &a[j + j *
				a_dim1]);
			a[i__3].r = z__1.r, a[i__3].i = z__1.i;
/* L20: */
		    }
		}
	    }

	} else if (*info == 0) {

	    *info = j;
	}

	if (j < min(*m,*n)) {

/*           Update trailing submatrix. */

	    i__2 = *m - j;
	    i__3 = *n - j;
	    z__1.r = -1., z__1.i = -0.;
	    zgeru_(&i__2, &i__3, &z__1, &a[j + 1 + j * a_dim1], &c__1, &a[j +
		    (j + 1) * a_dim1], lda, &a[j + 1 + (j + 1) * a_dim1], lda)
		    ;
	}
/* L10: */
    }
    return 0;

/*     End of ZGETF2 */

}