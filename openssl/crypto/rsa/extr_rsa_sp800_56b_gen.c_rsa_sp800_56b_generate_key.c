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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rsa_fips186_4_gen_prob_primes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rsa_sp800_56b_derive_params_from_pq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rsa_sp800_56b_pairwise_test (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_sp800_56b_validate_strength (int,int) ; 

int rsa_sp800_56b_generate_key(RSA *rsa, int nbits, const BIGNUM *efixed,
                               BN_GENCB *cb)
{
    int ret = 0;
    int ok;
    BN_CTX *ctx = NULL;
    BIGNUM *e = NULL;

    /* (Steps 1a-1b) : Currently ignores the strength check */
    if (!rsa_sp800_56b_validate_strength(nbits, -1))
        return 0;

    ctx = BN_CTX_new();
    if (ctx == NULL)
        return 0;

    /* Set default if e is not passed in */
    if (efixed == NULL) {
        e = BN_new();
        if (e == NULL || !BN_set_word(e, 65537))
            goto err;
    } else {
        e = (BIGNUM *)efixed;
    }
    /* (Step 1c) fixed exponent is checked later . */

    for (;;) {
        /* (Step 2) Generate prime factors */
        if (!rsa_fips186_4_gen_prob_primes(rsa, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, nbits, e, ctx, cb))
            goto err;
        /* (Steps 3-5) Compute params d, n, dP, dQ, qInv */
        ok = rsa_sp800_56b_derive_params_from_pq(rsa, nbits, e, ctx);
        if (ok < 0)
            goto err;
        if (ok > 0)
            break;
        /* Gets here if computed d is too small - so try again */
    }

    /* (Step 6) Do pairwise test - optional validity test has been omitted */
    ret = rsa_sp800_56b_pairwise_test(rsa, ctx);
err:
    if (efixed == NULL)
        BN_free(e);
    BN_CTX_free(ctx);
    return ret;
}