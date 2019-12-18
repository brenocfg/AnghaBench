#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * n; int /*<<< orphan*/ * e; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int BN_PRIMETEST_COMPOSITE_NOT_POWER_OF_PRIME ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_F_RSA_SP800_56B_CHECK_PUBLIC ; 
 int /*<<< orphan*/  RSA_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  RSA_R_INVALID_MODULUS ; 
 int /*<<< orphan*/  RSA_R_PUB_EXPONENT_OUT_OF_RANGE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_get0_small_factors () ; 
 int bn_miller_rabin_is_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  rsa_check_public_exponent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_sp800_56b_validate_strength (int,int) ; 

int rsa_sp800_56b_check_public(const RSA *rsa)
{
    int ret = 0, nbits, status;
    BN_CTX *ctx = NULL;
    BIGNUM *gcd = NULL;

    if (rsa->n == NULL || rsa->e == NULL)
        return 0;

    /*
     * (Step a): modulus must be 2048 or 3072 (caveat from SP800-56Br1)
     * NOTE: changed to allow keys >= 2048
     */
    nbits = BN_num_bits(rsa->n);
    if (!rsa_sp800_56b_validate_strength(nbits, -1)) {
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_PUBLIC, RSA_R_INVALID_KEY_LENGTH);
        return 0;
    }
    if (!BN_is_odd(rsa->n)) {
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_PUBLIC, RSA_R_INVALID_MODULUS);
        return 0;
    }

    /* (Steps b-c): 2^16 < e < 2^256, n and e must be odd */
    if (!rsa_check_public_exponent(rsa->e)) {
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_PUBLIC,
               RSA_R_PUB_EXPONENT_OUT_OF_RANGE);
        return 0;
    }

    ctx = BN_CTX_new();
    gcd = BN_new();
    if (ctx == NULL || gcd == NULL)
        goto err;

    /* (Steps d-f):
     * The modulus is composite, but not a power of a prime.
     * The modulus has no factors smaller than 752.
     */
    if (!BN_gcd(gcd, rsa->n, bn_get0_small_factors(), ctx) || !BN_is_one(gcd)) {
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_PUBLIC, RSA_R_INVALID_MODULUS);
        goto err;
    }

    ret = bn_miller_rabin_is_prime(rsa->n, 0, ctx, NULL, 1, &status);
    if (ret != 1 || status != BN_PRIMETEST_COMPOSITE_NOT_POWER_OF_PRIME) {
        RSAerr(RSA_F_RSA_SP800_56B_CHECK_PUBLIC, RSA_R_INVALID_MODULUS);
        ret = 0;
        goto err;
    }

    ret = 1;
err:
    BN_free(gcd);
    BN_CTX_free(ctx);
    return ret;
}