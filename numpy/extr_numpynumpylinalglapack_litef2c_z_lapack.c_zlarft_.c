#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* logical ;
typedef  int integer ;
struct TYPE_7__ {int r; int i; } ;
typedef  TYPE_1__ doublecomplex ;

/* Variables and functions */
 int c__1 ; 
 TYPE_1__ c_b56 ; 
 int max (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  zlacgv_ (int*,TYPE_1__*,int*) ; 

int zlarft_(char *direct, char *storev, integer *n, integer *
	k, doublecomplex *v, integer *ldv, doublecomplex *tau, doublecomplex *
	t, integer *ldt)
{
    /* System generated locals */
    integer t_dim1, t_offset, v_dim1, v_offset, i__1, i__2, i__3, i__4;
    doublecomplex z__1;

    /* Local variables */
    static integer i__, j, prevlastv;
    static doublecomplex vii;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int zgemv_(char *, integer *, integer *,
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *,
	    integer *, doublecomplex *, doublecomplex *, integer *);
    static integer lastv;
    extern /* Subroutine */ int ztrmv_(char *, char *, char *, integer *,
	    doublecomplex *, integer *, doublecomplex *, integer *), zlacgv_(integer *, doublecomplex *, integer *);


/*
    -- LAPACK auxiliary routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    ZLARFT forms the triangular factor T of a complex block reflector H
    of order n, which is defined as a product of k elementary reflectors.

    If DIRECT = 'F', H = H(1) H(2) . . . H(k) and T is upper triangular;

    If DIRECT = 'B', H = H(k) . . . H(2) H(1) and T is lower triangular.

    If STOREV = 'C', the vector which defines the elementary reflector
    H(i) is stored in the i-th column of the array V, and

       H  =  I - V * T * V'

    If STOREV = 'R', the vector which defines the elementary reflector
    H(i) is stored in the i-th row of the array V, and

       H  =  I - V' * T * V

    Arguments
    =========

    DIRECT  (input) CHARACTER*1
            Specifies the order in which the elementary reflectors are
            multiplied to form the block reflector:
            = 'F': H = H(1) H(2) . . . H(k) (Forward)
            = 'B': H = H(k) . . . H(2) H(1) (Backward)

    STOREV  (input) CHARACTER*1
            Specifies how the vectors which define the elementary
            reflectors are stored (see also Further Details):
            = 'C': columnwise
            = 'R': rowwise

    N       (input) INTEGER
            The order of the block reflector H. N >= 0.

    K       (input) INTEGER
            The order of the triangular factor T (= the number of
            elementary reflectors). K >= 1.

    V       (input/output) COMPLEX*16 array, dimension
                                 (LDV,K) if STOREV = 'C'
                                 (LDV,N) if STOREV = 'R'
            The matrix V. See further details.

    LDV     (input) INTEGER
            The leading dimension of the array V.
            If STOREV = 'C', LDV >= max(1,N); if STOREV = 'R', LDV >= K.

    TAU     (input) COMPLEX*16 array, dimension (K)
            TAU(i) must contain the scalar factor of the elementary
            reflector H(i).

    T       (output) COMPLEX*16 array, dimension (LDT,K)
            The k by k triangular factor T of the block reflector.
            If DIRECT = 'F', T is upper triangular; if DIRECT = 'B', T is
            lower triangular. The rest of the array is not used.

    LDT     (input) INTEGER
            The leading dimension of the array T. LDT >= K.

    Further Details
    ===============

    The shape of the matrix V and the storage of the vectors which define
    the H(i) is best illustrated by the following example with n = 5 and
    k = 3. The elements equal to 1 are not stored; the corresponding
    array elements are modified but restored on exit. The rest of the
    array is not used.

    DIRECT = 'F' and STOREV = 'C':         DIRECT = 'F' and STOREV = 'R':

                 V = (  1       )                 V = (  1 v1 v1 v1 v1 )
                     ( v1  1    )                     (     1 v2 v2 v2 )
                     ( v1 v2  1 )                     (        1 v3 v3 )
                     ( v1 v2 v3 )
                     ( v1 v2 v3 )

    DIRECT = 'B' and STOREV = 'C':         DIRECT = 'B' and STOREV = 'R':

                 V = ( v1 v2 v3 )                 V = ( v1 v1  1       )
                     ( v1 v2 v3 )                     ( v2 v2 v2  1    )
                     (  1 v2 v3 )                     ( v3 v3 v3 v3  1 )
                     (     1 v3 )
                     (        1 )

    =====================================================================


       Quick return if possible
*/

    /* Parameter adjustments */
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    --tau;
    t_dim1 = *ldt;
    t_offset = 1 + t_dim1;
    t -= t_offset;

    /* Function Body */
    if (*n == 0) {
	return 0;
    }

    if (lsame_(direct, "F")) {
	prevlastv = *n;
	i__1 = *k;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    prevlastv = max(prevlastv,i__);
	    i__2 = i__;
	    if (tau[i__2].r == 0. && tau[i__2].i == 0.) {

/*              H(i)  =  I */

		i__2 = i__;
		for (j = 1; j <= i__2; ++j) {
		    i__3 = j + i__ * t_dim1;
		    t[i__3].r = 0., t[i__3].i = 0.;
/* L10: */
		}
	    } else {

/*              general case */

		i__2 = i__ + i__ * v_dim1;
		vii.r = v[i__2].r, vii.i = v[i__2].i;
		i__2 = i__ + i__ * v_dim1;
		v[i__2].r = 1., v[i__2].i = 0.;
		if (lsame_(storev, "C")) {
/*                 Skip any trailing zeros. */
		    i__2 = i__ + 1;
		    for (lastv = *n; lastv >= i__2; --lastv) {
			i__3 = lastv + i__ * v_dim1;
			if (v[i__3].r != 0. || v[i__3].i != 0.) {
			    goto L15;
			}
		    }
L15:
		    j = min(lastv,prevlastv);

/*                 T(1:i-1,i) := - tau(i) * V(i:j,1:i-1)' * V(i:j,i) */

		    i__2 = j - i__ + 1;
		    i__3 = i__ - 1;
		    i__4 = i__;
		    z__1.r = -tau[i__4].r, z__1.i = -tau[i__4].i;
		    zgemv_("Conjugate transpose", &i__2, &i__3, &z__1, &v[i__
			    + v_dim1], ldv, &v[i__ + i__ * v_dim1], &c__1, &
			    c_b56, &t[i__ * t_dim1 + 1], &c__1);
		} else {
/*                 Skip any trailing zeros. */
		    i__2 = i__ + 1;
		    for (lastv = *n; lastv >= i__2; --lastv) {
			i__3 = i__ + lastv * v_dim1;
			if (v[i__3].r != 0. || v[i__3].i != 0.) {
			    goto L16;
			}
		    }
L16:
		    j = min(lastv,prevlastv);

/*                 T(1:i-1,i) := - tau(i) * V(1:i-1,i:j) * V(i,i:j)' */

		    if (i__ < j) {
			i__2 = j - i__;
			zlacgv_(&i__2, &v[i__ + (i__ + 1) * v_dim1], ldv);
		    }
		    i__2 = i__ - 1;
		    i__3 = j - i__ + 1;
		    i__4 = i__;
		    z__1.r = -tau[i__4].r, z__1.i = -tau[i__4].i;
		    zgemv_("No transpose", &i__2, &i__3, &z__1, &v[i__ *
			    v_dim1 + 1], ldv, &v[i__ + i__ * v_dim1], ldv, &
			    c_b56, &t[i__ * t_dim1 + 1], &c__1);
		    if (i__ < j) {
			i__2 = j - i__;
			zlacgv_(&i__2, &v[i__ + (i__ + 1) * v_dim1], ldv);
		    }
		}
		i__2 = i__ + i__ * v_dim1;
		v[i__2].r = vii.r, v[i__2].i = vii.i;

/*              T(1:i-1,i) := T(1:i-1,1:i-1) * T(1:i-1,i) */

		i__2 = i__ - 1;
		ztrmv_("Upper", "No transpose", "Non-unit", &i__2, &t[
			t_offset], ldt, &t[i__ * t_dim1 + 1], &c__1);
		i__2 = i__ + i__ * t_dim1;
		i__3 = i__;
		t[i__2].r = tau[i__3].r, t[i__2].i = tau[i__3].i;
		if (i__ > 1) {
		    prevlastv = max(prevlastv,lastv);
		} else {
		    prevlastv = lastv;
		}
	    }
/* L20: */
	}
    } else {
	prevlastv = 1;
	for (i__ = *k; i__ >= 1; --i__) {
	    i__1 = i__;
	    if (tau[i__1].r == 0. && tau[i__1].i == 0.) {

/*              H(i)  =  I */

		i__1 = *k;
		for (j = i__; j <= i__1; ++j) {
		    i__2 = j + i__ * t_dim1;
		    t[i__2].r = 0., t[i__2].i = 0.;
/* L30: */
		}
	    } else {

/*              general case */

		if (i__ < *k) {
		    if (lsame_(storev, "C")) {
			i__1 = *n - *k + i__ + i__ * v_dim1;
			vii.r = v[i__1].r, vii.i = v[i__1].i;
			i__1 = *n - *k + i__ + i__ * v_dim1;
			v[i__1].r = 1., v[i__1].i = 0.;
/*                    Skip any leading zeros. */
			i__1 = i__ - 1;
			for (lastv = 1; lastv <= i__1; ++lastv) {
			    i__2 = lastv + i__ * v_dim1;
			    if (v[i__2].r != 0. || v[i__2].i != 0.) {
				goto L35;
			    }
			}
L35:
			j = max(lastv,prevlastv);

/*
                      T(i+1:k,i) :=
                              - tau(i) * V(j:n-k+i,i+1:k)' * V(j:n-k+i,i)
*/

			i__1 = *n - *k + i__ - j + 1;
			i__2 = *k - i__;
			i__3 = i__;
			z__1.r = -tau[i__3].r, z__1.i = -tau[i__3].i;
			zgemv_("Conjugate transpose", &i__1, &i__2, &z__1, &v[
				j + (i__ + 1) * v_dim1], ldv, &v[j + i__ *
				v_dim1], &c__1, &c_b56, &t[i__ + 1 + i__ *
				t_dim1], &c__1);
			i__1 = *n - *k + i__ + i__ * v_dim1;
			v[i__1].r = vii.r, v[i__1].i = vii.i;
		    } else {
			i__1 = i__ + (*n - *k + i__) * v_dim1;
			vii.r = v[i__1].r, vii.i = v[i__1].i;
			i__1 = i__ + (*n - *k + i__) * v_dim1;
			v[i__1].r = 1., v[i__1].i = 0.;
/*                    Skip any leading zeros. */
			i__1 = i__ - 1;
			for (lastv = 1; lastv <= i__1; ++lastv) {
			    i__2 = i__ + lastv * v_dim1;
			    if (v[i__2].r != 0. || v[i__2].i != 0.) {
				goto L36;
			    }
			}
L36:
			j = max(lastv,prevlastv);

/*
                      T(i+1:k,i) :=
                              - tau(i) * V(i+1:k,j:n-k+i) * V(i,j:n-k+i)'
*/

			i__1 = *n - *k + i__ - 1 - j + 1;
			zlacgv_(&i__1, &v[i__ + j * v_dim1], ldv);
			i__1 = *k - i__;
			i__2 = *n - *k + i__ - j + 1;
			i__3 = i__;
			z__1.r = -tau[i__3].r, z__1.i = -tau[i__3].i;
			zgemv_("No transpose", &i__1, &i__2, &z__1, &v[i__ +
				1 + j * v_dim1], ldv, &v[i__ + j * v_dim1],
				ldv, &c_b56, &t[i__ + 1 + i__ * t_dim1], &
				c__1);
			i__1 = *n - *k + i__ - 1 - j + 1;
			zlacgv_(&i__1, &v[i__ + j * v_dim1], ldv);
			i__1 = i__ + (*n - *k + i__) * v_dim1;
			v[i__1].r = vii.r, v[i__1].i = vii.i;
		    }

/*                 T(i+1:k,i) := T(i+1:k,i+1:k) * T(i+1:k,i) */

		    i__1 = *k - i__;
		    ztrmv_("Lower", "No transpose", "Non-unit", &i__1, &t[i__
			    + 1 + (i__ + 1) * t_dim1], ldt, &t[i__ + 1 + i__ *
			     t_dim1], &c__1)
			    ;
		    if (i__ > 1) {
			prevlastv = min(prevlastv,lastv);
		    } else {
			prevlastv = lastv;
		    }
		}
		i__1 = i__ + i__ * t_dim1;
		i__2 = i__;
		t[i__1].r = tau[i__2].r, t[i__1].i = tau[i__2].i;
	    }
/* L40: */
	}
    }
    return 0;

/*     End of ZLARFT */

}