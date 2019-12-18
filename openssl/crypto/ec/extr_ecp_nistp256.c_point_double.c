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
typedef  int /*<<< orphan*/  smallfelem ;
typedef  int /*<<< orphan*/  longfelem ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff_zero107 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_reduce_zero105 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_scalar (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  felem_shrink (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_small_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_sum (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  longfelem_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longfelem_scalar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smallfelem_square (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
point_double(felem x_out, felem y_out, felem z_out,
             const felem x_in, const felem y_in, const felem z_in)
{
    longfelem tmp, tmp2;
    felem delta, gamma, beta, alpha, ftmp, ftmp2;
    smallfelem small1, small2;

    felem_assign(ftmp, x_in);
    /* ftmp[i] < 2^106 */
    felem_assign(ftmp2, x_in);
    /* ftmp2[i] < 2^106 */

    /* delta = z^2 */
    felem_square(tmp, z_in);
    felem_reduce(delta, tmp);
    /* delta[i] < 2^101 */

    /* gamma = y^2 */
    felem_square(tmp, y_in);
    felem_reduce(gamma, tmp);
    /* gamma[i] < 2^101 */
    felem_shrink(small1, gamma);

    /* beta = x*gamma */
    felem_small_mul(tmp, small1, x_in);
    felem_reduce(beta, tmp);
    /* beta[i] < 2^101 */

    /* alpha = 3*(x-delta)*(x+delta) */
    felem_diff(ftmp, delta);
    /* ftmp[i] < 2^105 + 2^106 < 2^107 */
    felem_sum(ftmp2, delta);
    /* ftmp2[i] < 2^105 + 2^106 < 2^107 */
    felem_scalar(ftmp2, 3);
    /* ftmp2[i] < 3 * 2^107 < 2^109 */
    felem_mul(tmp, ftmp, ftmp2);
    felem_reduce(alpha, tmp);
    /* alpha[i] < 2^101 */
    felem_shrink(small2, alpha);

    /* x' = alpha^2 - 8*beta */
    smallfelem_square(tmp, small2);
    felem_reduce(x_out, tmp);
    felem_assign(ftmp, beta);
    felem_scalar(ftmp, 8);
    /* ftmp[i] < 8 * 2^101 = 2^104 */
    felem_diff(x_out, ftmp);
    /* x_out[i] < 2^105 + 2^101 < 2^106 */

    /* z' = (y + z)^2 - gamma - delta */
    felem_sum(delta, gamma);
    /* delta[i] < 2^101 + 2^101 = 2^102 */
    felem_assign(ftmp, y_in);
    felem_sum(ftmp, z_in);
    /* ftmp[i] < 2^106 + 2^106 = 2^107 */
    felem_square(tmp, ftmp);
    felem_reduce(z_out, tmp);
    felem_diff(z_out, delta);
    /* z_out[i] < 2^105 + 2^101 < 2^106 */

    /* y' = alpha*(4*beta - x') - 8*gamma^2 */
    felem_scalar(beta, 4);
    /* beta[i] < 4 * 2^101 = 2^103 */
    felem_diff_zero107(beta, x_out);
    /* beta[i] < 2^107 + 2^103 < 2^108 */
    felem_small_mul(tmp, small2, beta);
    /* tmp[i] < 7 * 2^64 < 2^67 */
    smallfelem_square(tmp2, small1);
    /* tmp2[i] < 7 * 2^64 */
    longfelem_scalar(tmp2, 8);
    /* tmp2[i] < 8 * 7 * 2^64 = 7 * 2^67 */
    longfelem_diff(tmp, tmp2);
    /* tmp[i] < 2^67 + 2^70 + 2^40 < 2^71 */
    felem_reduce_zero105(y_out, tmp);
    /* y_out[i] < 2^106 */
}