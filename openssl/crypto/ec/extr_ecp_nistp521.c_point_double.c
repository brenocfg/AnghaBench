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
typedef  int /*<<< orphan*/  largefelem ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_diff64 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_diff_128_64 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_scalar128 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  felem_scalar64 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_sum64 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
point_double(felem x_out, felem y_out, felem z_out,
             const felem x_in, const felem y_in, const felem z_in)
{
    largefelem tmp, tmp2;
    felem delta, gamma, beta, alpha, ftmp, ftmp2;

    felem_assign(ftmp, x_in);
    felem_assign(ftmp2, x_in);

    /* delta = z^2 */
    felem_square(tmp, z_in);
    felem_reduce(delta, tmp);   /* delta[i] < 2^59 + 2^14 */

    /* gamma = y^2 */
    felem_square(tmp, y_in);
    felem_reduce(gamma, tmp);   /* gamma[i] < 2^59 + 2^14 */

    /* beta = x*gamma */
    felem_mul(tmp, x_in, gamma);
    felem_reduce(beta, tmp);    /* beta[i] < 2^59 + 2^14 */

    /* alpha = 3*(x-delta)*(x+delta) */
    felem_diff64(ftmp, delta);
    /* ftmp[i] < 2^61 */
    felem_sum64(ftmp2, delta);
    /* ftmp2[i] < 2^60 + 2^15 */
    felem_scalar64(ftmp2, 3);
    /* ftmp2[i] < 3*2^60 + 3*2^15 */
    felem_mul(tmp, ftmp, ftmp2);
    /*-
     * tmp[i] < 17(3*2^121 + 3*2^76)
     *        = 61*2^121 + 61*2^76
     *        < 64*2^121 + 64*2^76
     *        = 2^127 + 2^82
     *        < 2^128
     */
    felem_reduce(alpha, tmp);

    /* x' = alpha^2 - 8*beta */
    felem_square(tmp, alpha);
    /*
     * tmp[i] < 17*2^120 < 2^125
     */
    felem_assign(ftmp, beta);
    felem_scalar64(ftmp, 8);
    /* ftmp[i] < 2^62 + 2^17 */
    felem_diff_128_64(tmp, ftmp);
    /* tmp[i] < 2^125 + 2^63 + 2^62 + 2^17 */
    felem_reduce(x_out, tmp);

    /* z' = (y + z)^2 - gamma - delta */
    felem_sum64(delta, gamma);
    /* delta[i] < 2^60 + 2^15 */
    felem_assign(ftmp, y_in);
    felem_sum64(ftmp, z_in);
    /* ftmp[i] < 2^60 + 2^15 */
    felem_square(tmp, ftmp);
    /*
     * tmp[i] < 17(2^122) < 2^127
     */
    felem_diff_128_64(tmp, delta);
    /* tmp[i] < 2^127 + 2^63 */
    felem_reduce(z_out, tmp);

    /* y' = alpha*(4*beta - x') - 8*gamma^2 */
    felem_scalar64(beta, 4);
    /* beta[i] < 2^61 + 2^16 */
    felem_diff64(beta, x_out);
    /* beta[i] < 2^61 + 2^60 + 2^16 */
    felem_mul(tmp, alpha, beta);
    /*-
     * tmp[i] < 17*((2^59 + 2^14)(2^61 + 2^60 + 2^16))
     *        = 17*(2^120 + 2^75 + 2^119 + 2^74 + 2^75 + 2^30)
     *        = 17*(2^120 + 2^119 + 2^76 + 2^74 + 2^30)
     *        < 2^128
     */
    felem_square(tmp2, gamma);
    /*-
     * tmp2[i] < 17*(2^59 + 2^14)^2
     *         = 17*(2^118 + 2^74 + 2^28)
     */
    felem_scalar128(tmp2, 8);
    /*-
     * tmp2[i] < 8*17*(2^118 + 2^74 + 2^28)
     *         = 2^125 + 2^121 + 2^81 + 2^77 + 2^35 + 2^31
     *         < 2^126
     */
    felem_diff128(tmp, tmp2);
    /*-
     * tmp[i] < 2^127 - 2^69 + 17(2^120 + 2^119 + 2^76 + 2^74 + 2^30)
     *        = 2^127 + 2^124 + 2^122 + 2^120 + 2^118 + 2^80 + 2^78 + 2^76 +
     *          2^74 + 2^69 + 2^34 + 2^30
     *        < 2^128
     */
    felem_reduce(y_out, tmp);
}