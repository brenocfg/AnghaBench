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
typedef  int integer ;

/* Variables and functions */
 int max (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  slarfg_ (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xerbla_ (char*,int*) ; 

int sgelq2_(integer *m, integer *n, real *a, integer *lda,
	real *tau, real *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer i__, k;
    static real aii;
    extern /* Subroutine */ int slarf_(char *, integer *, integer *, real *,
	    integer *, real *, real *, integer *, real *), xerbla_(
	    char *, integer *), slarfg_(integer *, real *, real *,
	    integer *, real *);


/*
    -- LAPACK routine (version 3.2.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       June 2010


    Purpose
    =======

    SGELQ2 computes an LQ factorization of a real m by n matrix A:
    A = L * Q.

    Arguments
    =========

    M       (input) INTEGER
            The number of rows of the matrix A.  M >= 0.

    N       (input) INTEGER
            The number of columns of the matrix A.  N >= 0.

    A       (input/output) REAL array, dimension (LDA,N)
            On entry, the m by n matrix A.
            On exit, the elements on and below the diagonal of the array
            contain the m by min(m,n) lower trapezoidal matrix L (L is
            lower triangular if m <= n); the elements above the diagonal,
            with the array TAU, represent the orthogonal matrix Q as a
            product of elementary reflectors (see Further Details).

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= max(1,M).

    TAU     (output) REAL array, dimension (min(M,N))
            The scalar factors of the elementary reflectors (see Further
            Details).

    WORK    (workspace) REAL array, dimension (M)

    INFO    (output) INTEGER
            = 0: successful exit
            < 0: if INFO = -i, the i-th argument had an illegal value

    Further Details
    ===============

    The matrix Q is represented as a product of elementary reflectors

       Q = H(k) . . . H(2) H(1), where k = min(m,n).

    Each H(i) has the form

       H(i) = I - tau * v * v'

    where tau is a real scalar, and v is a real vector with
    v(1:i-1) = 0 and v(i) = 1; v(i+1:n) is stored on exit in A(i,i+1:n),
    and tau in TAU(i).

    =====================================================================


       Test the input arguments
*/

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

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
	xerbla_("SGELQ2", &i__1);
	return 0;
    }

    k = min(*m,*n);

    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {

/*        Generate elementary reflector H(i) to annihilate A(i,i+1:n) */

	i__2 = *n - i__ + 1;
/* Computing MIN */
	i__3 = i__ + 1;
	slarfg_(&i__2, &a[i__ + i__ * a_dim1], &a[i__ + min(i__3,*n) * a_dim1]
		, lda, &tau[i__]);
	if (i__ < *m) {

/*           Apply H(i) to A(i+1:m,i:n) from the right */

	    aii = a[i__ + i__ * a_dim1];
	    a[i__ + i__ * a_dim1] = 1.f;
	    i__2 = *m - i__;
	    i__3 = *n - i__ + 1;
	    slarf_("Right", &i__2, &i__3, &a[i__ + i__ * a_dim1], lda, &tau[
		    i__], &a[i__ + 1 + i__ * a_dim1], lda, &work[1]);
	    a[i__ + i__ * a_dim1] = aii;
	}
/* L10: */
    }
    return 0;

/*     End of SGELQ2 */

}