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
struct TYPE_5__ {int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; int /*<<< orphan*/ * e; int /*<<< orphan*/  const* n; int /*<<< orphan*/ * d; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RSA_F_RSA_SP800_56B_CHECK_KEYPAIR ; 
 int /*<<< orphan*/  RSA_R_INVALID_KEYPAIR ; 
 int /*<<< orphan*/  RSA_R_INVALID_REQUEST ; 
 int /*<<< orphan*/  RSA_R_PUB_EXPONENT_OUT_OF_RANGE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rsa_check_crt_components (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ rsa_check_pminusq_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ rsa_check_prime_factor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ rsa_check_private_exponent (TYPE_1__ const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_check_public_exponent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_sp800_56b_validate_strength (int,int) ; 

int rsa_sp800_56b_check_keypair(const RSA *rsa, const BIGNUM *efixed,
                                int strength, int nbits)
{
    int ret = 0;
    BN_CTX *ctx = NULL;
    BIGNUM *r = NULL;

    if (rsa->p == NULL
            || rsa->q == NULL
            || rsa->e == NULL
            || rsa->d == NULL
            || rsa->n == NULL) {
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_KEYPAIR, RSA_R_INVALID_REQUEST);
        return 0;
    }
    /* (Step 1): Check Ranges */
    if (!rsa_sp800_56b_validate_strength(nbits, strength))
        return 0;

    /* If the exponent is known */
    if (efixed != NULL) {
        /* (2): Check fixed exponent matches public exponent. */
        if (BN_cmp(efixed, rsa->e) != 0) {
            RSAerr(RSA_F_RSA_SP800_56B_CHECK_KEYPAIR, RSA_R_INVALID_REQUEST);
            return 0;
        }
    }
    /* (Step 1.c): e is odd integer 65537 <= e < 2^256 */
    if (!rsa_check_public_exponent(rsa->e)) {
        /* exponent out of range */
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_KEYPAIR,
               RSA_R_PUB_EXPONENT_OUT_OF_RANGE);
        return 0;
    }
    /* (Step 3.b): check the modulus */
    if (nbits != BN_num_bits(rsa->n)) {
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_KEYPAIR, RSA_R_INVALID_KEYPAIR);
        return 0;
    }

    ctx = BN_CTX_new();
    if (ctx == NULL)
        return 0;

    BN_CTX_start(ctx);
    r = BN_CTX_get(ctx);
    if (r == NULL || !BN_mul(r, rsa->p, rsa->q, ctx))
        goto err;
    /* (Step 4.c): Check n = pq */
    if (BN_cmp(rsa->n, r) != 0) {
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_KEYPAIR, RSA_R_INVALID_REQUEST);
        goto err;
    }

    /* (Step 5): check prime factors p & q */
    ret = rsa_check_prime_factor(rsa->p, rsa->e, nbits, ctx)
          && rsa_check_prime_factor(rsa->q, rsa->e, nbits, ctx)
          && (rsa_check_pminusq_diff(r, rsa->p, rsa->q, nbits) > 0)
          /* (Step 6): Check the private exponent d */
          && rsa_check_private_exponent(rsa, nbits, ctx)
          /* 6.4.1.2.3 (Step 7): Check the CRT components */
          && rsa_check_crt_components(rsa, ctx);
    if (ret != 1)
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_KEYPAIR, RSA_R_INVALID_KEYPAIR);

err:
    BN_clear(r);
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}