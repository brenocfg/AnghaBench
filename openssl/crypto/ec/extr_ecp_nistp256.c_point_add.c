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
typedef  int /*<<< orphan*/  const smallfelem ;
typedef  int /*<<< orphan*/  longfelem ;
typedef  scalar_t__ limb ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  copy_conditional (int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  copy_small_conditional (int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff_zero107 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_reduce_zero105 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_scalar (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  felem_shrink (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_small_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_small_sum (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_sum (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  longfelem_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longfelem_scalar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  point_double (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 scalar_t__ smallfelem_is_zero (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  smallfelem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  smallfelem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void point_add(felem x3, felem y3, felem z3,
                      const felem x1, const felem y1, const felem z1,
                      const int mixed, const smallfelem x2,
                      const smallfelem y2, const smallfelem z2)
{
    felem ftmp, ftmp2, ftmp3, ftmp4, ftmp5, ftmp6, x_out, y_out, z_out;
    longfelem tmp, tmp2;
    smallfelem small1, small2, small3, small4, small5;
    limb x_equal, y_equal, z1_is_zero, z2_is_zero;

    felem_shrink(small3, z1);

    z1_is_zero = smallfelem_is_zero(small3);
    z2_is_zero = smallfelem_is_zero(z2);

    /* ftmp = z1z1 = z1**2 */
    smallfelem_square(tmp, small3);
    felem_reduce(ftmp, tmp);
    /* ftmp[i] < 2^101 */
    felem_shrink(small1, ftmp);

    if (!mixed) {
        /* ftmp2 = z2z2 = z2**2 */
        smallfelem_square(tmp, z2);
        felem_reduce(ftmp2, tmp);
        /* ftmp2[i] < 2^101 */
        felem_shrink(small2, ftmp2);

        felem_shrink(small5, x1);

        /* u1 = ftmp3 = x1*z2z2 */
        smallfelem_mul(tmp, small5, small2);
        felem_reduce(ftmp3, tmp);
        /* ftmp3[i] < 2^101 */

        /* ftmp5 = z1 + z2 */
        felem_assign(ftmp5, z1);
        felem_small_sum(ftmp5, z2);
        /* ftmp5[i] < 2^107 */

        /* ftmp5 = (z1 + z2)**2 - (z1z1 + z2z2) = 2z1z2 */
        felem_square(tmp, ftmp5);
        felem_reduce(ftmp5, tmp);
        /* ftmp2 = z2z2 + z1z1 */
        felem_sum(ftmp2, ftmp);
        /* ftmp2[i] < 2^101 + 2^101 = 2^102 */
        felem_diff(ftmp5, ftmp2);
        /* ftmp5[i] < 2^105 + 2^101 < 2^106 */

        /* ftmp2 = z2 * z2z2 */
        smallfelem_mul(tmp, small2, z2);
        felem_reduce(ftmp2, tmp);

        /* s1 = ftmp2 = y1 * z2**3 */
        felem_mul(tmp, y1, ftmp2);
        felem_reduce(ftmp6, tmp);
        /* ftmp6[i] < 2^101 */
    } else {
        /*
         * We'll assume z2 = 1 (special case z2 = 0 is handled later)
         */

        /* u1 = ftmp3 = x1*z2z2 */
        felem_assign(ftmp3, x1);
        /* ftmp3[i] < 2^106 */

        /* ftmp5 = 2z1z2 */
        felem_assign(ftmp5, z1);
        felem_scalar(ftmp5, 2);
        /* ftmp5[i] < 2*2^106 = 2^107 */

        /* s1 = ftmp2 = y1 * z2**3 */
        felem_assign(ftmp6, y1);
        /* ftmp6[i] < 2^106 */
    }

    /* u2 = x2*z1z1 */
    smallfelem_mul(tmp, x2, small1);
    felem_reduce(ftmp4, tmp);

    /* h = ftmp4 = u2 - u1 */
    felem_diff_zero107(ftmp4, ftmp3);
    /* ftmp4[i] < 2^107 + 2^101 < 2^108 */
    felem_shrink(small4, ftmp4);

    x_equal = smallfelem_is_zero(small4);

    /* z_out = ftmp5 * h */
    felem_small_mul(tmp, small4, ftmp5);
    felem_reduce(z_out, tmp);
    /* z_out[i] < 2^101 */

    /* ftmp = z1 * z1z1 */
    smallfelem_mul(tmp, small1, small3);
    felem_reduce(ftmp, tmp);

    /* s2 = tmp = y2 * z1**3 */
    felem_small_mul(tmp, y2, ftmp);
    felem_reduce(ftmp5, tmp);

    /* r = ftmp5 = (s2 - s1)*2 */
    felem_diff_zero107(ftmp5, ftmp6);
    /* ftmp5[i] < 2^107 + 2^107 = 2^108 */
    felem_scalar(ftmp5, 2);
    /* ftmp5[i] < 2^109 */
    felem_shrink(small1, ftmp5);
    y_equal = smallfelem_is_zero(small1);

    if (x_equal && y_equal && !z1_is_zero && !z2_is_zero) {
        point_double(x3, y3, z3, x1, y1, z1);
        return;
    }

    /* I = ftmp = (2h)**2 */
    felem_assign(ftmp, ftmp4);
    felem_scalar(ftmp, 2);
    /* ftmp[i] < 2*2^108 = 2^109 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);

    /* J = ftmp2 = h * I */
    felem_mul(tmp, ftmp4, ftmp);
    felem_reduce(ftmp2, tmp);

    /* V = ftmp4 = U1 * I */
    felem_mul(tmp, ftmp3, ftmp);
    felem_reduce(ftmp4, tmp);

    /* x_out = r**2 - J - 2V */
    smallfelem_square(tmp, small1);
    felem_reduce(x_out, tmp);
    felem_assign(ftmp3, ftmp4);
    felem_scalar(ftmp4, 2);
    felem_sum(ftmp4, ftmp2);
    /* ftmp4[i] < 2*2^101 + 2^101 < 2^103 */
    felem_diff(x_out, ftmp4);
    /* x_out[i] < 2^105 + 2^101 */

    /* y_out = r(V-x_out) - 2 * s1 * J */
    felem_diff_zero107(ftmp3, x_out);
    /* ftmp3[i] < 2^107 + 2^101 < 2^108 */
    felem_small_mul(tmp, small1, ftmp3);
    felem_mul(tmp2, ftmp6, ftmp2);
    longfelem_scalar(tmp2, 2);
    /* tmp2[i] < 2*2^67 = 2^68 */
    longfelem_diff(tmp, tmp2);
    /* tmp[i] < 2^67 + 2^70 + 2^40 < 2^71 */
    felem_reduce_zero105(y_out, tmp);
    /* y_out[i] < 2^106 */

    copy_small_conditional(x_out, x2, z1_is_zero);
    copy_conditional(x_out, x1, z2_is_zero);
    copy_small_conditional(y_out, y2, z1_is_zero);
    copy_conditional(y_out, y1, z2_is_zero);
    copy_small_conditional(z_out, z2, z1_is_zero);
    copy_conditional(z_out, z1, z2_is_zero);
    felem_assign(x3, x_out);
    felem_assign(y3, y_out);
    felem_assign(z3, z_out);
}