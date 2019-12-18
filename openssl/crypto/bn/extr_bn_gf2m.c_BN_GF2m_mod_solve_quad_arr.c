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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_F_BN_GF2M_MOD_SOLVE_QUAD_ARR ; 
 int /*<<< orphan*/  BN_GF2m_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_GF2m_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_GF2m_mod_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const*) ; 
 int /*<<< orphan*/  BN_GF2m_mod_mul_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GF2m_mod_sqr_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_ONE ; 
 int /*<<< orphan*/  BN_R_NO_SOLUTION ; 
 int /*<<< orphan*/  BN_R_TOO_MANY_ITERATIONS ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_priv_rand_ex (int /*<<< orphan*/  const*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_ITERATIONS ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_GF2m_mod_solve_quad_arr(BIGNUM *r, const BIGNUM *a_, const int p[],
                               BN_CTX *ctx)
{
    int ret = 0, count = 0, j;
    BIGNUM *a, *z, *rho, *w, *w2, *tmp;

    bn_check_top(a_);

    if (p[0] == 0) {
        /* reduction mod 1 => return 0 */
        BN_zero(r);
        return 1;
    }

    BN_CTX_start(ctx);
    a = BN_CTX_get(ctx);
    z = BN_CTX_get(ctx);
    w = BN_CTX_get(ctx);
    if (w == NULL)
        goto err;

    if (!BN_GF2m_mod_arr(a, a_, p))
        goto err;

    if (BN_is_zero(a)) {
        BN_zero(r);
        ret = 1;
        goto err;
    }

    if (p[0] & 0x1) {           /* m is odd */
        /* compute half-trace of a */
        if (!BN_copy(z, a))
            goto err;
        for (j = 1; j <= (p[0] - 1) / 2; j++) {
            if (!BN_GF2m_mod_sqr_arr(z, z, p, ctx))
                goto err;
            if (!BN_GF2m_mod_sqr_arr(z, z, p, ctx))
                goto err;
            if (!BN_GF2m_add(z, z, a))
                goto err;
        }

    } else {                    /* m is even */

        rho = BN_CTX_get(ctx);
        w2 = BN_CTX_get(ctx);
        tmp = BN_CTX_get(ctx);
        if (tmp == NULL)
            goto err;
        do {
            if (!BN_priv_rand_ex(rho, p[0], BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY,
                                 ctx))
                goto err;
            if (!BN_GF2m_mod_arr(rho, rho, p))
                goto err;
            BN_zero(z);
            if (!BN_copy(w, rho))
                goto err;
            for (j = 1; j <= p[0] - 1; j++) {
                if (!BN_GF2m_mod_sqr_arr(z, z, p, ctx))
                    goto err;
                if (!BN_GF2m_mod_sqr_arr(w2, w, p, ctx))
                    goto err;
                if (!BN_GF2m_mod_mul_arr(tmp, w2, a, p, ctx))
                    goto err;
                if (!BN_GF2m_add(z, z, tmp))
                    goto err;
                if (!BN_GF2m_add(w, w2, rho))
                    goto err;
            }
            count++;
        } while (BN_is_zero(w) && (count < MAX_ITERATIONS));
        if (BN_is_zero(w)) {
            BNerr(BN_F_BN_GF2M_MOD_SOLVE_QUAD_ARR, BN_R_TOO_MANY_ITERATIONS);
            goto err;
        }
    }

    if (!BN_GF2m_mod_sqr_arr(w, z, p, ctx))
        goto err;
    if (!BN_GF2m_add(w, z, w))
        goto err;
    if (BN_GF2m_cmp(w, a)) {
        BNerr(BN_F_BN_GF2M_MOD_SOLVE_QUAD_ARR, BN_R_NO_SOLUTION);
        goto err;
    }

    if (!BN_copy(r, z))
        goto err;
    bn_check_top(r);

    ret = 1;

 err:
    BN_CTX_end(ctx);
    return ret;
}