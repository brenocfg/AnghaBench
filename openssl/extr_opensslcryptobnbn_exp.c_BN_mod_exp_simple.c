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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_F_BN_MOD_EXP_SIMPLE ; 
 scalar_t__ BN_abs_is_word (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_get_flags (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_bit_set (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_nnmod (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int BN_one (int /*<<< orphan*/ *) ; 
 int BN_window_bits_for_exponent_size (int) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 
 int TABLE_SIZE ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 

int BN_mod_exp_simple(BIGNUM *r, const BIGNUM *a, const BIGNUM *p,
                      const BIGNUM *m, BN_CTX *ctx)
{
    int i, j, bits, ret = 0, wstart, wend, window, wvalue;
    int start = 1;
    BIGNUM *d;
    /* Table of variables obtained from 'ctx' */
    BIGNUM *val[TABLE_SIZE];

    if (BN_get_flags(p, BN_FLG_CONSTTIME) != 0
            || BN_get_flags(a, BN_FLG_CONSTTIME) != 0
            || BN_get_flags(m, BN_FLG_CONSTTIME) != 0) {
        /* BN_FLG_CONSTTIME only supported by BN_mod_exp_mont() */
        BNerr(BN_F_BN_MOD_EXP_SIMPLE, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return 0;
    }

    bits = BN_num_bits(p);
    if (bits == 0) {
        /* x**0 mod 1, or x**0 mod -1 is still zero. */
        if (BN_abs_is_word(m, 1)) {
            ret = 1;
            BN_zero(r);
        } else {
            ret = BN_one(r);
        }
        return ret;
    }

    BN_CTX_start(ctx);
    d = BN_CTX_get(ctx);
    val[0] = BN_CTX_get(ctx);
    if (val[0] == NULL)
        goto err;

    if (!BN_nnmod(val[0], a, m, ctx))
        goto err;               /* 1 */
    if (BN_is_zero(val[0])) {
        BN_zero(r);
        ret = 1;
        goto err;
    }

    window = BN_window_bits_for_exponent_size(bits);
    if (window > 1) {
        if (!BN_mod_mul(d, val[0], val[0], m, ctx))
            goto err;           /* 2 */
        j = 1 << (window - 1);
        for (i = 1; i < j; i++) {
            if (((val[i] = BN_CTX_get(ctx)) == NULL) ||
                !BN_mod_mul(val[i], val[i - 1], d, m, ctx))
                goto err;
        }
    }

    start = 1;                  /* This is used to avoid multiplication etc
                                 * when there is only the value '1' in the
                                 * buffer. */
    wvalue = 0;                 /* The 'value' of the window */
    wstart = bits - 1;          /* The top bit of the window */
    wend = 0;                   /* The bottom bit of the window */

    if (!BN_one(r))
        goto err;

    for (;;) {
        if (BN_is_bit_set(p, wstart) == 0) {
            if (!start)
                if (!BN_mod_mul(r, r, r, m, ctx))
                    goto err;
            if (wstart == 0)
                break;
            wstart--;
            continue;
        }
        /*
         * We now have wstart on a 'set' bit, we now need to work out how bit
         * a window to do.  To do this we need to scan forward until the last
         * set bit before the end of the window
         */
        j = wstart;
        wvalue = 1;
        wend = 0;
        for (i = 1; i < window; i++) {
            if (wstart - i < 0)
                break;
            if (BN_is_bit_set(p, wstart - i)) {
                wvalue <<= (i - wend);
                wvalue |= 1;
                wend = i;
            }
        }

        /* wend is the size of the current window */
        j = wend + 1;
        /* add the 'bytes above' */
        if (!start)
            for (i = 0; i < j; i++) {
                if (!BN_mod_mul(r, r, r, m, ctx))
                    goto err;
            }

        /* wvalue will be an odd number < 2^window */
        if (!BN_mod_mul(r, r, val[wvalue >> 1], m, ctx))
            goto err;

        /* move the 'window' down further */
        wstart -= wend + 1;
        wvalue = 0;
        start = 0;
        if (wstart < 0)
            break;
    }
    ret = 1;
 err:
    BN_CTX_end(ctx);
    bn_check_top(r);
    return ret;
}